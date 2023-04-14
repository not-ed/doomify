#include "jsonpaletteloader.h"

Palette JsonPaletteLoader::LoadFile(QString file_path) {
    fileLoadOutcome = UNKNOWN;
    Palette loaded_palette;

    std::ifstream opened_file;
    opened_file.open(file_path.toStdString(), std::ios::in);

    std::string json_data;

    if (opened_file.is_open()){
        for (std::string read_line; std::getline(opened_file,read_line);) {
            json_data += read_line;
        }
    }
    else
    {
        fileLoadOutcome = FAILURE;
        return loaded_palette;
    }

    opened_file.close();

    nlohmann::json parsed_json;

    try {
        parsed_json = nlohmann::json::parse(json_data);
    }
    catch (std::exception &e)
    {
        fileLoadOutcome = FAILURE;
        return loaded_palette;
    }

    if (parsed_json.contains("colors")){
        for (auto color : parsed_json["colors"]){
            bool has_all_color_channels = color.contains("red") && color.contains("green") && color.contains("blue");
            if (has_all_color_channels) {
                QColor new_color = QColor(color["red"].get<int>(), color["green"].get<int>(), color["blue"].get<int>());
                loaded_palette.colors.insert(loaded_palette.colors.begin(),new_color);
            }
            else if (!loaded_palette.colors.empty()){
                fileLoadOutcome = MISSING_COLORS;
            }
        }
    }
    else
    {
        fileLoadOutcome = FAILURE;
        return loaded_palette;
    }

    bool has_name = parsed_json.contains("name") && parsed_json["name"].is_string();
    loaded_palette.displayName = QString::fromStdString( has_name ? parsed_json["name"].get<std::string>() : QFileInfo(file_path).fileName().toStdString());

    if (fileLoadOutcome == UNKNOWN) fileLoadOutcome = SUCCESSFUL;
    return loaded_palette;
}

#include "gplpaletteloader.h"
#include <iostream>
Palette GplPaletteLoader::LoadFile(QString file_path) {
    fileLoadOutcome = UNKNOWN;
    Palette loaded_palette;

    std::ifstream opened_file;
    opened_file.open(file_path.toStdString(), std::ios::in);

    std::string read_name;

    if (opened_file.is_open()){
        std::string read_line;
        std::getline(opened_file,read_line);

        bool has_gimp_palette_indicator = QString(read_line.c_str()).trimmed().toLower() != "gimp palette";
        if (has_gimp_palette_indicator){
            fileLoadOutcome = FAILURE;
            return loaded_palette;
        }

        while (!opened_file.eof()){
            std::getline(opened_file,read_line);

            bool line_is_comment = QString(read_line.c_str()).trimmed().startsWith("#");
            if (line_is_comment){
                continue;
            }

            if (read_name.empty()){
                bool line_is_name = QString(read_line.c_str()).trimmed().toLower().startsWith("name:");
                if (line_is_name){
                    read_name = QString(read_line.c_str()).remove("name:",Qt::CaseInsensitive).trimmed().toStdString();
                    continue;
                }
            }

            QStringList split_line = QString(read_line.c_str()).simplified().split(" ");
            if(split_line.length() >= 3){
                bool red_value_is_valid;
                int red_value = split_line[0].toInt(&red_value_is_valid);
                red_value_is_valid = red_value_is_valid && (0 <= red_value && red_value <= 255);
                bool green_value_is_valid;
                int green_value = split_line[1].toInt(&green_value_is_valid);
                green_value_is_valid = green_value_is_valid && (0 <= green_value && green_value <= 255);
                bool blue_value_is_valid;
                int blue_value = split_line[2].toInt(&blue_value_is_valid);
                blue_value_is_valid = blue_value_is_valid && (0 <= blue_value && blue_value <= 255);

                if (red_value_is_valid && green_value_is_valid && blue_value_is_valid){
                    loaded_palette.colors.insert(loaded_palette.colors.begin(), QColor(red_value, green_value, blue_value));
                }
                else if (!loaded_palette.colors.empty()) {
                    fileLoadOutcome = MISSING_COLORS;
                }
            }
        }
    }
    else
    {
        fileLoadOutcome = FAILURE;
        return loaded_palette;
    }

    opened_file.close();

    loaded_palette.displayName = read_name.empty() ? QFileInfo(file_path).fileName() : QString(read_name.c_str());

    if (fileLoadOutcome == UNKNOWN) fileLoadOutcome = SUCCESSFUL;
    return loaded_palette;
}

#include "palettes.h"
#include <iostream>
//TODO: Parse other palette file formats? (ASE, GPL, JASC, HEX etc.)

std::vector<Palette> LoadPalettesFromDisk(){
    std::vector<Palette> palette_list;

    QDirIterator palettes_dir("./palettes", QDir::Files, QDirIterator::Subdirectories);

    // Yeah, no.
    // TODO: As more palette formats are worked in, we will need to refactor this to at least be more cleaner at some point.
    while (palettes_dir.hasNext()) {
        QString file = palettes_dir.next();

        // If file extension is 'dmfy'
        if(QFileInfo(file).completeSuffix().compare(QString("dmfy"),Qt::CaseInsensitive) == 0) {
            Palette loaded_palette = ParseDmfyFile(QFileInfo(file).filePath());

            if (!loaded_palette.colors.empty()) palette_list.insert(palette_list.end(),loaded_palette);
        }

        // If file extension is 'GPL'
        if(QFileInfo(file).completeSuffix().compare(QString("gpl"),Qt::CaseInsensitive) == 0) {
            Palette loaded_palette = ParseGplFile(QFileInfo(file).filePath());

            if (!loaded_palette.colors.empty()) palette_list.insert(palette_list.end(),loaded_palette);
        }

        // If file extension is 'json'
        if(QFileInfo(file).completeSuffix().compare(QString("json"),Qt::CaseInsensitive) == 0) {
            Palette loaded_palette = ParseJsonFile(QFileInfo(file).filePath());

            if (!loaded_palette.colors.empty()) palette_list.insert(palette_list.end(),loaded_palette);
        }
    }
    
    return palette_list;
}

Palette ParseDmfyFile(QString path){
    Palette pal;

    std::ifstream opened_file;
    opened_file.open(path.toStdString(),std::ios::binary);
    if(opened_file.is_open()){
        // Read how many characters are in the palette's name
        int name_char_count = 0;
        opened_file.read((char*)&name_char_count,1);

        // Read the palette's name
        char pal_name[name_char_count];
        // Null-terminate the char string lest we get junk characters at the end of the palette's name when read
        pal_name[name_char_count] = '\0';
        opened_file.read(pal_name,name_char_count);
        pal.displayName = pal_name;

        // Read how many colors are in the palette
        int color_byte_count = 0;
        int color_count = 0;
        // Read how many bytes must be read first to get a complete number count
        opened_file.read((char*)&color_byte_count,1);
        opened_file.read((char*)&color_count,color_byte_count);

        while (!opened_file.eof()){
            int c_red = 0;
            int c_green = 0;
            int c_blue = 0;

            opened_file.read((char*)&c_red,1);
            opened_file.read((char*)&c_green,1);
            opened_file.read((char*)&c_blue,1);

            QColor c = QColor(c_red,c_green,c_blue);

            pal.colors.insert(pal.colors.begin(),c);
        }

        opened_file.close();
    }

    return pal;
}

Palette ParseGplFile(QString path){
    Palette pal;

    std::ifstream opened_file;
    opened_file.open(path.toStdString(), std::ios::in);

    while (!opened_file.eof()){
        int c_red = 0;
        int c_green = 0;
        int c_blue = 0;

        opened_file >> c_red;
        opened_file >> c_green;
        opened_file >> c_blue;

        // If we invoked a read error by reading a non-int, skip past this line and continue.
        if (opened_file.fail()){
            opened_file.clear();
            opened_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }

        opened_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        pal.colors.insert(pal.colors.begin(),QColor(c_red,c_green,c_blue));
    }

    opened_file.close();

    pal.displayName = QFileInfo(path).fileName();

    return pal;
}

Palette ParseJsonFile(QString path){
    Palette pal;

    std::ifstream opened_file;
    opened_file.open(path.toStdString(), std::ios::in);

    std::string json_data;

    if (opened_file.is_open()){
        for (std::string read_line; std::getline(opened_file,read_line);) {
            json_data += read_line;
        }
    }
    else
    {
        return pal;
    }

    opened_file.close();

    auto parsed_json = nlohmann::json::parse(json_data);

    for (auto color : parsed_json["colors"]){
        QColor new_color = QColor(color["red"].get<int>(), color["green"].get<int>(), color["blue"].get<int>());
        pal.colors.insert(pal.colors.begin(),new_color);
    }

    pal.displayName = QString::fromStdString(parsed_json["name"].get<std::string>());
    return pal;
}
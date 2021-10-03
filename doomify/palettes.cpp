#include "palettes.h"

//TODO: Parse other palette file formats? (ASE, GPL, JASC, HEX etc.)

std::vector<Palette> LoadPalettesFromDisk(){
    std::vector<Palette> palette_list;

    QDirIterator palettes_dir("./palettes", QDir::Files, QDirIterator::Subdirectories);

    while (palettes_dir.hasNext()) {
        QString file = palettes_dir.next();

        // If file extension is 'dmfy'
        if(QFileInfo(file).completeSuffix().compare(QString("dmfy"),Qt::CaseInsensitive) == 0) {
            Palette loaded_palette = ParseDmfyFile(QFileInfo(file).filePath());

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
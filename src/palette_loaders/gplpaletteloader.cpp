#include "gplpaletteloader.h"

Palette GplPaletteLoader::LoadFile(QString file_path) {
    Palette loaded_palette;

    std::ifstream opened_file;
    opened_file.open(file_path.toStdString(), std::ios::in);

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

        loaded_palette.colors.insert(loaded_palette.colors.begin(), QColor(c_red, c_green, c_blue));
    }

    opened_file.close();

    loaded_palette.displayName = QFileInfo(file_path).fileName();

    fileLoadOutcome = SUCCESSFUL;
    return loaded_palette;
}

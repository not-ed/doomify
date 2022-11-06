#include "palettemanager.h"

std::vector<Palette> PaletteManager::PullAllPalettesFromDisk() {
    std::vector<Palette> palette_list;

    QDirIterator palette_files("./palettes", QDir::Files, QDirIterator::Subdirectories);

    while (palette_files.hasNext()) {
        QString next_palette = palette_files.next();
        std::string next_palette_extension = QFileInfo(next_palette).completeSuffix().toStdString();

        // Do we actually have a loader / behaviour for this particular file's format?
        if (APPROPRIATE_LOADER.find(next_palette_extension) != APPROPRIATE_LOADER.end()){
            PaletteLoader* loader = APPROPRIATE_LOADER.at(next_palette_extension);
            Palette loaded_palette = loader->LoadFile(next_palette);

            // TODO: Could it be useful to add a user choice to continue using a palette even if there were issues loading it?
            // e.g. "This palette is missing colors, do you still want to use it?"
            if (loader->PreviousLoadWasSuccessful()) palette_list.insert(palette_list.end(),loaded_palette);
        }
    }

    return palette_list;
}
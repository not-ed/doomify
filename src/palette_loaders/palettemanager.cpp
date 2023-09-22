#include "palettemanager.h"
#include <iostream> //TODO: Temp

std::vector<Palette> PaletteManager::PullAllPalettesFromDisk() {
    std::vector<Palette> loaded_palettes;

    QDirIterator palette_files("./palettes", QDir::Files, QDirIterator::Subdirectories);

    while (palette_files.hasNext()) {
        auto next_palette_file = palette_files.next();
        auto next_palette_file_extension = QFileInfo(next_palette_file).completeSuffix();

        PaletteLoader* palette_loader = GetPaletteLoaderForFileExtension(next_palette_file_extension);
        auto supported_palette_loader_exists = palette_loader != nullptr;

        if (supported_palette_loader_exists){
            Palette loaded_palette = palette_loader->LoadFile(next_palette_file);

            // TODO: Could it be useful to add a user choice to continue using a palette even if there were issues loading it?
            // e.g. "This palette is missing colors, do you still want to use it?"
            if (palette_loader->PreviousLoadWasSuccessful())
                loaded_palettes.insert(loaded_palettes.end(), loaded_palette);
        }
    }

    return loaded_palettes;
}

void PaletteManager::ShowPalettesDirectory() {
    std::cout << "Clicked" << std::endl;
}

PaletteLoader* PaletteManager::GetPaletteLoaderForFileExtension(QString file_extension) {
    auto extension = file_extension.toLower().toStdString();

    if (PALETTE_LOADERS.find(extension) != PALETTE_LOADERS.end()){
        return PALETTE_LOADERS.at(extension);
    }
    return nullptr;
}
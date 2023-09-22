#pragma once
#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include "../palettes.h"
#include "gplpaletteloader.h"
#include "jsonpaletteloader.h"
#include <QString>
#include <QFileInfo>

class PaletteManager{
public:
    std::vector<Palette> PullAllPalettesFromDisk();
private:
    PaletteLoader* GetPaletteLoaderForFileExtension(QString file_extension);
    GplPaletteLoader gplLoader = GplPaletteLoader();
    JsonPaletteLoader jsonLoader = JsonPaletteLoader();
    const std::map <std::string, PaletteLoader*> PALETTE_LOADERS {
        {"gpl",&gplLoader},
        {"json",&jsonLoader},
    };
};

#endif
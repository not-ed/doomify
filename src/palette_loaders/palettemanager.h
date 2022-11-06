#pragma once
#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include "../palettes.h"
#include "gplpaletteloader.h"
#include <QString>
#include <QFileInfo>

class PaletteManager{
public:
    std::vector<Palette> PullAllPalettesFromDisk();
private:
    GplPaletteLoader gplLoader = GplPaletteLoader();

    const std::map <std::string, PaletteLoader*> APPROPRIATE_LOADER {
        {"gpl",&gplLoader},
    };
};

#endif
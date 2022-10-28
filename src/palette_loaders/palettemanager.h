#pragma once
#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include "../palettes.h"
#include "gplpaletteloader.h"

class PaletteManager{
public:
    std::list<Palette> PullAllPalettesFromDisk();
private:
    GplPaletteLoader GplLoader = GplPaletteLoader();
};

#endif
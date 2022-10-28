#pragma once
#ifndef PALETTEMANAGER_H
#define PALETTEMANAGER_H

#include "../palettes.h"

class PaletteManager{
public:
    std::list<Palette> PullAllPalettesFromDisk();
};

#endif
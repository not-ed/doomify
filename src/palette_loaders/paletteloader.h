#pragma once
#ifndef PALETTELOADER_H
#define PALETTELOADER_H

#include "../palettes.h"
#include "paletteloaderoutcome.h"

class PaletteLoader{
public:
    virtual Palette LoadFile(QString file_path) = 0;
    bool PreviousLoadWasSuccessful(){ return fileLoadOutcome == SUCCESSFUL;}

protected:
    PaletteLoaderOutcome fileLoadOutcome = UNKNOWN;
};

#endif
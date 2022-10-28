#pragma once
#ifndef GPLPALETTELOADER_H
#define GPLPALETTELOADER_H

#include "paletteloader.h"

class GplPaletteLoader : public PaletteLoader{
    Palette LoadFile(QString file_path);
};

#endif
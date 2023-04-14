#pragma once
#ifndef JSONPALETTELOADER_H
#define JSONPALETTELOADER_H

#include "paletteloader.h"

class JsonPaletteLoader : public PaletteLoader{
    Palette LoadFile(QString file_path);
};

#endif
#pragma once
#ifndef IMAGESCHEMA_H
#define IMAGESCHEMA_H

#include "palettes.h"
#include <QColor>

struct ImageSchema{
    int width, height;
    bool usingImageDimensions;
    Palette palette;
    bool transparent;
    QColor backgroundColor;

    ImageSchema(){
        width = 64;
        height = 64;
        usingImageDimensions = false;
        palette.colors.clear();
        transparent = false;
        backgroundColor = QColor();
    }
};

#endif

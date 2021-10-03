#pragma once
#ifndef IMAGEGENERATION_H
#define IMAGEGENERATION_H

#include "imageschema.h"
#include <QColor>
#include <QPainter>

struct GeneratedImage{
    QImage image;
    ImageSchema schema;
};

GeneratedImage GenerateImage(QImage image, ImageSchema properties);
QColor GetClosestColor(QColor original, std::vector<QColor> colors);

#endif //IMAGEGENERATION_H
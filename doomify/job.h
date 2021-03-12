#pragma once
#ifndef JOB_H
#define JOB_H

#include "palettes.h"
#include <QString>
#include <QColor>
#include <QImage>
#include <vector>
#include <QPainter>
#include <QImageWriter>
#include <QFileDialog>

enum PALETTE_SOURCE{
    HARD, // Hard-coded palette (see palettes.h)
    IMAGE, // Taken from an image, considered temporary.
};

class Job
{
public:
    Job(QString image_path);
    ~Job();

    QImage GetSourceImage() {return sourceImage;}
    void SetOutputSize(int width, int height) {outputWidth = width; outputHeight = height;}
    int GetOutputWidth(){return outputWidth;}
    int GetOutputHeight(){return outputHeight;}
    void SetBackgroundColor(QColor color){backgroundColor = color;}

    void SetSourceImage(QString path);
    QImage GenerateOutput();
    QColor GetClosestColorFromPalette(QColor original_color, const std::vector<QColor>* palette);
    void SetPalette(int index);
    void SetPalette(QString image_path);
    void Export();
private:
    QImage sourceImage;
    QImage outputImage;
    int outputWidth;
    int outputHeight;
    QColor backgroundColor;

    PALETTE_SOURCE currentPaletteType = HARD;
    const std::vector<QColor>* currentHardPalette = &PALETTES::DOOM;
    std::vector<QColor>* currentImagePalette = nullptr;

    void ClearCustomPalette();
};

#endif
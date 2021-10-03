#pragma once
#ifndef PALETTES_H
#define PALETTES_H

#include <vector>
#include <QString>
#include <QColor>
#include <QDirIterator>
#include <fstream>

struct Palette{
    QString displayName;
    std::vector<QColor> colors;
};

std::vector<Palette> LoadPalettesFromDisk();
Palette ParseDmfyFile(QString path);

#endif
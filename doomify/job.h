#pragma once
#ifndef JOB_H
#define JOB_H

#include "imageschema.h"
#include "imagegeneration.h"
#include <QString>
#include <QColor>
#include <QImage>
#include <vector>
#include <QFileDialog>

class Job
{
public:
    Job(QString image_path);

    void UpdateSourceImageSizeToggle(bool new_state);
    void UpdateOutputWidth(int new_size);
    void UpdateOutputHeight(int new_size);
    void UpdateBackgroundAlpha(bool new_state);
    void UpdateRedBackgroundChannel(int new_value);
    void UpdateGreenBackgroundChannel(int new_value);
    void UpdateBlueBackgroundChannel(int new_value);
    void UpdatePalette(Palette pal);

    void RegenerateOutput();
    void Export();

    bool IsDirty(){return dirty;}
    QImage GetSourceImage() {return sourceImage;}
    // This does not guarantee the most up-to-date version of the output image is displayed! RegenerateOutput should be called first in such scenarios.
    QImage GetRoughOutputImage(){return outputImage.image;}
    bool UsingSourceImageSize(){return properties.usingImageDimensions;}
    int GetOutputWidth(){return properties.width;}
    int GetOutputHeight(){return properties.height;}
    bool IsTransparent(){return properties.transparent;}
    QColor GetBackgroundColor(){return properties.backgroundColor;}
    QString GetPaletteName() {return properties.palette.displayName;}

private:
    // Is the job's parameters out of sync with what is being displayed/last generated?
    bool dirty;
    bool UpdateDirtyFlag();

    QImage sourceImage;
    ImageSchema properties;
    GeneratedImage outputImage;
};

#endif
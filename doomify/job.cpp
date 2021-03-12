#include "job.h"

Job::Job(QString image_path){
    SetSourceImage(image_path);
}

Job::~Job(){
    ClearCustomPalette();
}

void Job::SetSourceImage(QString path){
    // Because every case where a path would be passed here is through a file select prompt, a path can be assumed to be valid
    sourceImage = QImage(path);

    SetOutputSize(sourceImage.width(),sourceImage.height());
    SetBackgroundColor(QColor(0,0,0,0));
}

QImage Job::GenerateOutput(){
    QImage source = sourceImage.scaled(QSize(GetOutputWidth(),GetOutputHeight()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    outputImage = QImage(GetOutputWidth(),GetOutputHeight(),QImage::Format_ARGB32);

    for (int i = 0; i < GetOutputHeight(); i++)
    {
        for (int ii = 0; ii < GetOutputWidth(); ii++)
        {
            QColor reference_color = source.pixelColor(QPoint(ii,i));
            QColor closest_color;

            if(currentPaletteType == HARD){
            closest_color = GetClosestColorFromPalette(reference_color,currentHardPalette);
            }else{
            closest_color = GetClosestColorFromPalette(reference_color,currentImagePalette);
            }

            closest_color.setAlpha(reference_color.alpha());
            outputImage.setPixelColor(QPoint(ii,i),closest_color);
        }
    }

    QImage res = QImage(GetOutputWidth(),GetOutputHeight(),QImage::Format_ARGB32);
    res.fill(backgroundColor);
    QPainter paint;
    paint.begin(&res);
    paint.setCompositionMode(QPainter::CompositionMode_SourceOver);
    paint.drawImage(QPoint(0,0),outputImage);
    paint.end();

    return res;
}

QColor Job::GetClosestColorFromPalette(QColor original_color, const std::vector<QColor>* palette){
    int closest_index = 0;
    int closest_combined_offset = 0;

    for (int i = 0; i < palette->size(); i++)
    {
        int i_offset = 0;
        i_offset += abs(original_color.red() - palette->at(i).red());
        i_offset += abs(original_color.green() - palette->at(i).green());
        i_offset += abs(original_color.blue() - palette->at(i).blue());

        if(i != 0){
            if (i_offset < closest_combined_offset)
            {
                closest_index = i;
                closest_combined_offset = i_offset;
            }   
        }else{
            closest_index = i;
            closest_combined_offset = i_offset;
        }
    }
    
    return palette->at(closest_index);
}

void Job::SetPalette(int index){
    ClearCustomPalette();

    if (index >= 0 && index <= HARD_PALETTES.size()-1){
        currentHardPalette = HARD_PALETTES.at(index);
    }else{
        currentHardPalette = &PALETTES::ERROR;
    }

    currentPaletteType = HARD;
}

void Job::SetPalette(QString image_path){
    ClearCustomPalette();

    QImage img = QImage(image_path);

    currentImagePalette = new std::vector<QColor>;

    for (int i = 0; i < img.width(); i++)
    {
        for (int j = 0; j < img.height(); j++)
        {
            QColor pixel = img.pixel(QPoint(i,j));
            pixel.setAlpha(255);
             
            // No colors exist yet
            if (currentImagePalette->empty())
            {
                currentImagePalette->push_back(pixel);
            }else{
                bool is_new = true;
                for (int k = 0; k < currentImagePalette->size(); k++)
                {
                    // Color is already present
                    if(pixel == currentImagePalette->at(k)){ 
                        is_new = false;
                        break;
                    }
                }
                if(is_new){currentImagePalette->push_back(pixel);}
            }
        }
    }

    currentPaletteType = PALETTE_SOURCE::IMAGE;
}

void Job::ClearCustomPalette(){
    if (currentImagePalette != nullptr)
    {
        delete currentImagePalette;
        currentImagePalette = nullptr;
    }
}

void Job::Export(){
    //TODO: Move FileDialogs from here and mainwindow.cpp into their own files.
    QFileDialog imageSaveDialog;
    imageSaveDialog.setAcceptMode(QFileDialog::AcceptSave);
    imageSaveDialog.setFileMode(QFileDialog::AnyFile);
    const QStringList filters({"PNG File (*.png)","BMP File (*.bmp)","JPEG File (*.JPG *.JPEG)"});
    const QStringList suffix_list({"PNG", "BMP", "JPG"});
    imageSaveDialog.setNameFilters(filters);

    if(imageSaveDialog.exec()){
        QString save_path = imageSaveDialog.selectedFiles()[0];
        QString selected_suffix = suffix_list.at(filters.indexOf(imageSaveDialog.selectedNameFilter()));

        QImage output = GenerateOutput();
        output.save(save_path,selected_suffix.toStdString().c_str(),100);
    }
}
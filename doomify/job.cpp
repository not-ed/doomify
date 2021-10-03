#include "job.h"

Job::Job(QString image_path){
    sourceImage = QImage(image_path);
    dirty = true;
    RegenerateOutput();
}

void Job::UpdateSourceImageSizeToggle(bool new_state){
    properties.usingImageDimensions = new_state;
    dirty = UpdateDirtyFlag();
}

void Job::UpdateOutputWidth(int new_size) {
    properties.width = new_size;
    dirty = UpdateDirtyFlag();
}

void Job::UpdateOutputHeight(int new_size) {
    properties.height = new_size;
    dirty = UpdateDirtyFlag();
}

void Job::UpdateBackgroundAlpha(bool new_state){
    properties.transparent = new_state;
    dirty = UpdateDirtyFlag();
}

void Job::UpdateRedBackgroundChannel(int new_value){
    properties.backgroundColor.setRed(new_value);
    dirty = UpdateDirtyFlag();
}

void Job::UpdateGreenBackgroundChannel(int new_value){
    properties.backgroundColor.setGreen(new_value);
    dirty = UpdateDirtyFlag();
}

void Job::UpdateBlueBackgroundChannel(int new_value){
    properties.backgroundColor.setBlue(new_value);
    dirty = UpdateDirtyFlag();
}

void Job::RegenerateOutput() {
    if(dirty){
        outputImage = GenerateImage(sourceImage,properties);
    }
}

void Job::Export(){
    //TODO: Open/save dialogs might be better off moved to mainwindow.cpp, particularly if multiple jobs need to be exported at once
    QFileDialog imageSaveDialog;
    imageSaveDialog.setAcceptMode(QFileDialog::AcceptSave);
    imageSaveDialog.setFileMode(QFileDialog::AnyFile);
    const QStringList filters({"PNG File (*.png)","BMP File (*.bmp)","JPEG File (*.JPG *.JPEG)"});
    const QStringList suffix_list({"PNG", "BMP", "JPG"});
    imageSaveDialog.setNameFilters(filters);
    //

    if(imageSaveDialog.exec()){
        QString save_path = imageSaveDialog.selectedFiles()[0];
        QString selected_suffix = suffix_list.at(filters.indexOf(imageSaveDialog.selectedNameFilter()));

        RegenerateOutput();
        outputImage.image.save(save_path,selected_suffix.toStdString().c_str(),100);
    }
}

bool Job::UpdateDirtyFlag() {
    //TODO
    return true;
}

void Job::UpdatePalette(Palette pal) {
    properties.palette = pal;
}
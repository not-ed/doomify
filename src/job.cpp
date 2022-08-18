#include "job.h"

Job::Job(QString image_path){
    sourceImageName =  QFileInfo(image_path).completeBaseName();
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

void Job::UpdatePalette(Palette pal) {
    properties.palette = pal;
    dirty = UpdateDirtyFlag();
}

void Job::RegenerateOutput() {
    if(dirty){
        outputImage = GenerateImage(sourceImage,properties);
        dirty = UpdateDirtyFlag();
    }
}

void Job::Export(){
    //TODO: Open/save dialogs might be better off moved to mainwindow.cpp, particularly if multiple jobs need to be exported at once
    // This is also being duplicated in mainwindow->ExportAllJobs();
    QFileDialog imageSaveDialog;
    imageSaveDialog.setAcceptMode(QFileDialog::AcceptSave);
    imageSaveDialog.setFileMode(QFileDialog::AnyFile);
    const QStringList filters({"PNG File (*.png)","BMP File (*.bmp)","JPEG File (*.JPG *.JPEG)"});
    const QStringList suffix_list({"PNG", "BMP", "JPG"});
    imageSaveDialog.setNameFilters(filters);
    //

    if(imageSaveDialog.exec()){
        std::string save_path = imageSaveDialog.selectedFiles()[0].toStdString();
        std::string extension = suffix_list.at(filters.indexOf(imageSaveDialog.selectedNameFilter())).toStdString();

        Export(save_path,extension);
    }
}

void Job::Export(std::string save_path, std::string extension) {
    RegenerateOutput();
    outputImage.image.save(save_path.c_str() ,extension.c_str(),100);
}

bool Job::UpdateDirtyFlag() {
    if (properties.usingImageDimensions != outputImage.schema.usingImageDimensions) return true;
    if (properties.width != outputImage.schema.width) return true;
    if (properties.height != outputImage.schema.height) return true;
    if (properties.palette.colors != outputImage.schema.palette.colors) return true;
    if (properties.transparent != outputImage.schema.transparent) return true;
    if (properties.backgroundColor != outputImage.schema.backgroundColor) return true;
    return false;
}
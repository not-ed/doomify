#include "mainwindow.h"
#include "./ui_mainwindow.h"

//TODO: Implementation of exporting multiple jobs at once needs to be implemented

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/assets/doomify.ico"));
    SetUpComponentConnections();
    SetUpImageDialog();
    SyncToSelectedJob();

    palettes = LoadPalettesFromDisk();
    for (auto p : palettes) {
        ui->comboBoxJobPalette->addItem(p.displayName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    //TODO: other jobs are not being freed - this includes job list widget items
    delete selectedJob;
}

void MainWindow::SetUpImageDialog(){
    imageOpenDialog.setAcceptMode(QFileDialog::AcceptOpen);
    imageOpenDialog.setFileMode(QFileDialog::ExistingFile);
    const QStringList filters({"Image Files (*.png *.jpeg *.jpg *.bmp)"});
    imageOpenDialog.setNameFilters(filters);
}

void MainWindow::SetUpComponentConnections(){
    // "Create New Job" button
    connect(ui->buttonNewJob, &QPushButton::pressed, this, &MainWindow::CreateNewJob);
    connect(ui->buttonUpdateJobPreview, &QPushButton::pressed, this, &MainWindow::OnPreviewUpdateRequested);

    // Job color palette box
    connect(ui->comboBoxJobPalette, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::OnPaletteSelection);

    // Job background color and background transparency checkbox
    connect(ui->spinBoxJobRed,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::OnBackgroundRedUpdate);
    connect(ui->spinBoxJobGreen,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::OnBackgroundGreenUpdate);
    connect(ui->spinBoxJobBlue,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::OnBackgroundBlueUpdate);
    connect(ui->checkBoxJobTransparency,QOverload<int>::of(&QCheckBox::stateChanged),this,&MainWindow::OnBackgroundAlphaToggle);

    //Job output size and "Use Original Image" checkbox
    connect(ui->checkBoxUseSourceSize,QOverload<int>::of(&QCheckBox::stateChanged),this,&MainWindow::OnJobSourceSizeToggle);
    connect(ui->spinBoxJobWidth,QOverload<int>::of(&QSpinBox::valueChanged),this, &MainWindow::OnJobWidthUpdate);
    connect(ui->spinBoxJobHeight,QOverload<int>::of(&QSpinBox::valueChanged),this, &MainWindow::OnJobHeightUpdate);

    // "Export Current Job" Button
    connect(ui->buttonExportCurrentJob,&QPushButton::pressed, this, &MainWindow::ExportCurrentJob);

    // Jobs List
    connect(ui->listWidgetJobs,&QListWidget::currentRowChanged, this, &MainWindow::OnJobSelection);
}

void MainWindow::SyncToSelectedJob() {
    bool job_exists = (selectedJob != nullptr);

    ui->groupBoxJobProperties->setEnabled(job_exists);
    ui->buttonExportCurrentJob->setEnabled(job_exists);

    if(job_exists){
        // Job output dimensions
        ui->checkBoxUseSourceSize->setChecked(selectedJob->UsingSourceImageSize());
        ui->spinBoxJobWidth->setEnabled(!selectedJob->UsingSourceImageSize());
        ui->spinBoxJobHeight->setEnabled(!selectedJob->UsingSourceImageSize());
        ui->spinBoxJobWidth->setValue(selectedJob->GetOutputWidth());
        ui->spinBoxJobHeight->setValue(selectedJob->GetOutputHeight());

        // Job background color values
        ui->checkBoxJobTransparency->setChecked(selectedJob->IsTransparent());
        ui->spinBoxJobRed->setEnabled(!ui->checkBoxJobTransparency->isChecked());
        ui->spinBoxJobGreen->setEnabled(!ui->checkBoxJobTransparency->isChecked());
        ui->spinBoxJobBlue->setEnabled(!ui->checkBoxJobTransparency->isChecked());
        QColor job_background = selectedJob->GetBackgroundColor();
        ui->spinBoxJobRed->setValue(job_background.red());
        ui->spinBoxJobGreen->setValue(job_background.green());
        ui->spinBoxJobBlue->setValue(job_background.blue());

        // Source and output image previews.
        QImage rough_preview = selectedJob->GetRoughOutputImage();
        ui->labelJobPreview->setPixmap(QPixmap::fromImage(rough_preview));
        ui->labelJobPreview->setPixmap(ui->labelJobPreview->pixmap()->scaled(ui->labelJobPreview->width(),ui->labelJobPreview->height(),Qt::KeepAspectRatio, Qt::FastTransformation));
        ui->labelRawImage->setPixmap(QPixmap::fromImage(selectedJob->GetSourceImage()));
        ui->labelRawImage->setPixmap(ui->labelRawImage->pixmap()->scaled(ui->labelRawImage->width(),ui->labelRawImage->height(),Qt::KeepAspectRatio, Qt::FastTransformation));

        // Displaying selected background color
        QPixmap selected_background_color(1,1);
        selected_background_color.fill(selectedJob->GetBackgroundColor());
        ui->labelJobBackground->setPixmap(selected_background_color);

        // Checking job "cleanliness"
        ui->buttonUpdateJobPreview->setEnabled(selectedJob->IsDirty());

        // Displaying selected palette name.
        int palette_index = ui->comboBoxJobPalette->findText(selectedJob->GetPaletteName());
        if (palette_index != -1){
            ui->comboBoxJobPalette->setCurrentText(palettes[palette_index].displayName);
        } else {
            ui->comboBoxJobPalette->setCurrentIndex(-1);
        }
    }
}

void MainWindow::OnPaletteSelection(int new_index) {
    if(selectedJob != nullptr && new_index != -1){
        selectedJob->UpdatePalette(palettes[new_index]);
        SyncToSelectedJob();
    }
}

void MainWindow::OnPreviewUpdateRequested() {
    if(selectedJob != nullptr){
        selectedJob->RegenerateOutput();
        SyncToSelectedJob();
    }
}

void MainWindow::OnJobSourceSizeToggle(bool new_state){
    if(selectedJob != nullptr){
        selectedJob->UpdateSourceImageSizeToggle(new_state);
        SyncToSelectedJob();
    }
}

void MainWindow::OnJobWidthUpdate(int new_width) {
    if(selectedJob != nullptr){
        selectedJob->UpdateOutputWidth(new_width);
        SyncToSelectedJob();
    }
}

void MainWindow::OnJobHeightUpdate(int new_width) {
    if(selectedJob != nullptr){
        selectedJob->UpdateOutputHeight(new_width);
        SyncToSelectedJob();
    }
}

void MainWindow::OnBackgroundAlphaToggle(bool new_state){
    if(selectedJob != nullptr){
        selectedJob->UpdateBackgroundAlpha(new_state);
        SyncToSelectedJob();
    }
}

void MainWindow::OnBackgroundRedUpdate(int new_value){
    if(selectedJob != nullptr){
        selectedJob->UpdateRedBackgroundChannel(new_value);
        SyncToSelectedJob();
    }
}

void MainWindow::OnBackgroundGreenUpdate(int new_value){
    if(selectedJob != nullptr){
        selectedJob->UpdateGreenBackgroundChannel(new_value);
        SyncToSelectedJob();
    }
}

void MainWindow::OnBackgroundBlueUpdate(int new_value){
    if(selectedJob != nullptr){
        selectedJob->UpdateBlueBackgroundChannel(new_value);
        SyncToSelectedJob();
    }
}

void MainWindow::OnJobSelection(int new_index) {
    //TODO
}

void MainWindow::CreateNewJob(){
    if (imageOpenDialog.exec())
    {
        selectedJob = new Job(imageOpenDialog.selectedFiles()[0]);
        selectedJob->UpdatePalette(palettes[0]);
        selectedJob->RegenerateOutput();

        QListWidgetItem* new_item = new QListWidgetItem;
        new_item->setText(QFileInfo(imageOpenDialog.selectedFiles()[0]).fileName());
        new_item->setIcon(QIcon(QPixmap::fromImage(selectedJob->GetSourceImage())));
        ui->listWidgetJobs->insertItem(0,new_item);

        SyncToSelectedJob();
    }
}

void MainWindow::ExportCurrentJob(){
    if (selectedJob != nullptr)
    {
        selectedJob->Export();
    }
}
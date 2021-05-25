#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qfile.h>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBoxJobPalette->addItems(HARD_PALETTE_NAMES);

    setWindowIcon(QIcon(":/assets/doomify.ico"));

    SetUpComponentConnections();
    SetUpImageDialog();
    UpdateJobRelevantUIState();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    connect(ui->buttonNewJob, &QPushButton::pressed, this, &MainWindow::UpdateJobRelevantUIState);
    // Job color palette box
    connect(ui->comboBoxJobPalette, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::OnJobPaletteChange);
    // Custom job palette / "..." button
    connect(ui->buttonCustomJobPalette,&QPushButton::pressed,this,&MainWindow::ImportCustomJobPalette);
    // Job background color and background transparency checkbox
    connect(ui->spinBoxJobRed,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::UpdateJobBackgroundColor);
    connect(ui->spinBoxJobGreen,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::UpdateJobBackgroundColor);
    connect(ui->spinBoxJobBlue,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::UpdateJobBackgroundColor);
    connect(ui->checkBoxJobTransparency,QOverload<int>::of(&QCheckBox::stateChanged),this,&MainWindow::UpdateJobBackgroundColor);
    //Job output size and "Use Original Image" checkbox
    connect(ui->spinBoxJobWidth,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::UpdateJobSize);
    connect(ui->spinBoxJobHeight,QOverload<int>::of(&QSpinBox::valueChanged),this,&MainWindow::UpdateJobSize);
    connect(ui->checkBoxUseSourceSize,QOverload<int>::of(&QCheckBox::stateChanged),this,&MainWindow::UpdateJobSize);
    // "Export Current Job" Button
    connect(ui->buttonExportCurrentJob,&QPushButton::pressed, this, &MainWindow::ExportCurrentJob);
}

void MainWindow::UpdateJobRelevantUIState(){
    bool job_available = (selectedJob != nullptr);

    ui->groupBoxJobProperties->setEnabled(job_available);
    ui->buttonExportCurrentJob->setEnabled(job_available);
}

void MainWindow::CreateNewJob(){
    if (imageOpenDialog.exec())
    {
        if(selectedJob != nullptr){
            delete selectedJob;
            selectedJob = nullptr;
        }

        SetJobOptionsToDefault();

        selectedJob = new Job(imageOpenDialog.selectedFiles()[0]);

        //Original Image Preview
        ui->labelRawImage->setPixmap(QPixmap::fromImage(selectedJob->GetSourceImage()));
        ui->labelRawImage->setPixmap(ui->labelRawImage->pixmap()->scaled(ui->labelRawImage->width(),ui->labelRawImage->height(),Qt::KeepAspectRatio, Qt::FastTransformation));

        UpdateJobOutputPreview();
    }
}

void MainWindow::OnJobPaletteChange(){    
    if(selectedJob != nullptr){
        selectedJob->SetPalette(ui->comboBoxJobPalette->currentIndex());
    }
    UpdateJobOutputPreview();
}

void MainWindow::UpdateJobBackgroundColor(){
    if (selectedJob != nullptr)
    {
        selectedJob->SetBackgroundColor(GetBackgroundSpinboxColor());
        // ui->labelJobPreview->setPixmap(QPixmap::fromImage(selectedJob->GenerateOutput()));
        // ui->labelJobPreview->setPixmap(ui->labelJobPreview->pixmap()->scaled(ui->labelJobPreview->width(),ui->labelJobPreview->height(),Qt::KeepAspectRatio, Qt::FastTransformation));
        UpdateJobOutputPreview();
    }else{
         QPixmap selCol(1,1);
         selCol.fill(GetBackgroundSpinboxColor());
         ui->labelJobBackground->setPixmap(selCol);
         ui->labelJobPreview->setPixmap(selCol);
    }

    if (ui->checkBoxJobTransparency->isChecked())
    {
        ui->spinBoxJobRed->setDisabled(true);
        ui->spinBoxJobGreen->setDisabled(true);
        ui->spinBoxJobBlue->setDisabled(true);
    }else{
        ui->spinBoxJobRed->setEnabled(true);
        ui->spinBoxJobGreen->setEnabled(true);
        ui->spinBoxJobBlue->setEnabled(true);
    }
}

QColor MainWindow::GetBackgroundSpinboxColor(){
    QColor new_color = QColor(ui->spinBoxJobRed->value(),ui->spinBoxJobGreen->value(),ui->spinBoxJobBlue->value(),!ui->checkBoxJobTransparency->isChecked() * 255);
    return new_color;
}

void MainWindow::UpdateJobOutputPreview(){
    ui->labelJobPreview->setPixmap(QPixmap::fromImage(selectedJob->GenerateOutput()));
    ui->labelJobPreview->setPixmap(ui->labelJobPreview->pixmap()->scaled(ui->labelJobPreview->width(),ui->labelJobPreview->height(),Qt::KeepAspectRatio, Qt::FastTransformation));
}

void MainWindow::UpdateJobSize(){
    if(selectedJob != nullptr){
        if(ui->checkBoxUseSourceSize->isChecked()){
            selectedJob->SetOutputSize(selectedJob->GetSourceImage().width(),selectedJob->GetSourceImage().height());
            ui->spinBoxJobWidth->setDisabled(true);
            ui->spinBoxJobHeight->setDisabled(true);
        }else{
            ui->spinBoxJobWidth->setEnabled(true);
            ui->spinBoxJobHeight->setEnabled(true);
            selectedJob->SetOutputSize(ui->spinBoxJobWidth->value(),ui->spinBoxJobHeight->value());
        }
        UpdateJobOutputPreview();
    }
}

void MainWindow::SetJobOptionsToDefault(){
    ui->checkBoxUseSourceSize->setChecked(true);

    ui->spinBoxJobWidth->setEnabled(true);
    ui->spinBoxJobWidth->setValue(64);
    ui->spinBoxJobWidth->setDisabled(true);

    ui->spinBoxJobHeight->setEnabled(true);
    ui->spinBoxJobHeight->setValue(64);
    ui->spinBoxJobHeight->setDisabled(true);

    ui->spinBoxJobRed->setEnabled(true);
    ui->spinBoxJobRed->setValue(0);
    ui->spinBoxJobRed->setDisabled(true);

    ui->spinBoxJobGreen->setEnabled(true);
    ui->spinBoxJobGreen->setValue(0);
    ui->spinBoxJobGreen->setDisabled(true);

    ui->spinBoxJobBlue->setEnabled(true);
    ui->spinBoxJobBlue->setValue(0);
    ui->spinBoxJobBlue->setDisabled(true);

    ui->checkBoxJobTransparency->setChecked(true);
}

void MainWindow::ImportCustomJobPalette(){
    if (selectedJob != nullptr)
    {
        if(imageOpenDialog.exec()){
            selectedJob->SetPalette(imageOpenDialog.selectedFiles()[0]);
            UpdateJobOutputPreview();
        }
    }
}

void MainWindow::ExportCurrentJob(){
    if (selectedJob != nullptr)
    {
        selectedJob->Export();
    }
}

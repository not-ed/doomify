#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "job.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QComboBox>
#include <QVector>
#include <QColor>
#include <QMessageBox>
#include <QInputDialog>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Job* selectedJob = nullptr;
    QFileDialog imageOpenDialog;

    void SetUpImageDialog();
    void SetUpComponentConnections();
    void UpdateJobRelevantUIState();
    void CreateNewJob();
    void OnJobPaletteChange();
    void UpdateJobBackgroundColor();
    QColor GetBackgroundSpinboxColor();
    void UpdateJobOutputPreview();
    void UpdateJobSize();
    void SetJobOptionsToDefault();
    void ImportCustomJobPalette();
    void ExportCurrentJob();
};

#endif
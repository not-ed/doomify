#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "job.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QComboBox>
#include <QListWidget>
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
    void SetUpComponentConnections();

    QFileDialog imageOpenDialog;
    void SetUpImageDialog();

    std::vector<Palette> palettes;

    void CreateNewJob();

    Job* selectedJob = nullptr;
    void SyncToSelectedJob();
    void OnPreviewUpdateRequested();
    void OnPaletteSelection(int new_index);
    void OnJobSourceSizeToggle(bool new_state);
    void OnJobWidthUpdate(int new_width);
    void OnJobHeightUpdate(int new_height);
    void OnBackgroundAlphaToggle(bool new_state);
    void OnBackgroundRedUpdate(int new_value);
    void OnBackgroundGreenUpdate(int new_value);
    void OnBackgroundBlueUpdate(int new_value);
    void OnJobSelection(int new_index);
    void ExportCurrentJob();
};

#endif
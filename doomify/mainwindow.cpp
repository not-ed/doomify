#include "mainwindow.h"
#include "./ui_mainwindow.h"

//TODO: REMOVE THIS
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// Tie button press to a function.
    connect(ui->loadButton, &QPushButton::pressed, this, &MainWindow::LoadImageFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadImageFile(){
    // File select/open dialog.
    QFileDialog test_dialog;
    test_dialog.setFileMode(QFileDialog::ExistingFile);
    const QStringList filters({
        "Image Files (*.png *.jpeg *.jpg *.bmp)",
        });
    test_dialog.setNameFilters(filters);
    test_dialog.exec();
}

#include "doomify.h"
#include "stdafx.h"

QImage originalImage;

doomify::doomify(QWidget *parent) : QWidget(parent)
{
    ui.setupUi(this);
    
    // Tie button press to a function.
    connect(ui.loadButton, &QToolButton::pressed, this, &doomify::LoadSourceImage);
}

void doomify::LoadSourceImage() {
    // File select/open dialog.
    QFileDialog test_dialog;
    test_dialog.setFileMode(QFileDialog::ExistingFile);
    const QStringList filters({
        "Image Files (*.png *.jpeg *.jpg *.bmp)",
        });
    test_dialog.setNameFilters(filters);
    test_dialog.exec();

    // If the user has selected a file and hasn't canceled the dialog box.
    if (test_dialog.result() != QDialog::DialogCode::Rejected) {
        //Upate images
        originalImage.load(test_dialog.selectedFiles()[0]);
        ui.originalPreview->setPixmap(test_dialog.selectedFiles()[0]);
    }
}
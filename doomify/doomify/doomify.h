#pragma once

#include <QtWidgets/QWidget>
#include "ui_doomify.h"

class doomify : public QWidget
{
    Q_OBJECT

public:
    doomify(QWidget *parent = Q_NULLPTR);

private:
    Ui::doomifyClass ui;
};

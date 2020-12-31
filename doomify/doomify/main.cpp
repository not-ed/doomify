#include "doomify.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    doomify w;
    w.show();
    return a.exec();
}

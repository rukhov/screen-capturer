#include "mainwindow.h"
#include "controller.h"
#include <QApplication>
#include "screenshot.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<ScreenShot>("ScreenShot");

    QApplication a(argc, argv);

    int retVal = -1;

    {
        Controller controller;

        MainWindow w(controller);

        w.show();

        retVal = a.exec();
    }

    return retVal;
}

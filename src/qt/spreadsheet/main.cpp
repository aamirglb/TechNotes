#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    //MainWindow mainWin;
    //mainWin.show();
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
    return app.exec();
}
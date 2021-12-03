#include <QApplication>
#include "window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto *mainWin = new DiagramWindow;
    mainWin->show();
    return app.exec();
}
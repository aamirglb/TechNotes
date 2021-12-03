#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto *window = new ColorNamesDialog;
    window->show();
    return app.exec();
}
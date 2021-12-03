#include <QApplication>
#include "directoryviewer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *window = new DirectoryViewer;
    window->show();
    return app.exec();
}
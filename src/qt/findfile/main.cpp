#include <QApplication>
#include "findfiledialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    FindFileDialog *window = new FindFileDialog;
    window->show();
    return app.exec();
}
#include <QApplication>
#include "preferencedialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PreferenceDialog *window = new PreferenceDialog;
    window->show();
    return app.exec();
}
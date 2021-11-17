#include <QApplication>

#include "sortdialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SortDialog *dialog = new SortDialog;
    dialog->setColumnRange('C', 'M');
    dialog->show();
    return app.exec();
}
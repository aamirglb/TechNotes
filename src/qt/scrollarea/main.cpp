#include <QApplication>
#include "iconeditor.h"
#include <QWidget>
#include <QScrollArea>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    IconEditor *iconEd = new IconEditor;
    iconEd->setIconImage(QImage(":/images/cross.png"));

    QScrollArea scrollArea;
    scrollArea.setWidget(iconEd);
    scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
    scrollArea.viewport()->setAutoFillBackground(true);
    scrollArea.setWindowTitle(QObject::tr("Icon Editor"));

    scrollArea.show();
    return app.exec();
}
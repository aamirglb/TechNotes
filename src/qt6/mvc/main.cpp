#include <QtGui>
#include <QApplication>

#include "customwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QScopedPointer<QWidget> widget(new CustomWidget());
    widget->resize(200, 400);
    widget->show();
    return app.exec();
}
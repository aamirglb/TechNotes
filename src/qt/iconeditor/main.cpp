#include <QApplication>
#include "iconeditor.h"
#include <QWidget>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    IconEditor *iconEd = new IconEditor;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(iconEd);
    window->setLayout(layout);
    window->show();
    return app.exec();
}
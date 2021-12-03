#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include "oventimer.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *ovenTimer = new OvenTimer;
//    ovenTimer->setFixedSize(200, 200);

    auto *button = new QPushButton("Set Timer");
    button->setDefault(true);
    auto *edit = new QLineEdit;

    QObject::connect(button, &QPushButton::clicked, [&](){
        ovenTimer->setDuration(edit->text().toInt());});

    auto *hLayout = new QHBoxLayout;
    hLayout->addWidget(edit);
    hLayout->addWidget(button);

    auto *vLayout = new QVBoxLayout;
    vLayout->addWidget(ovenTimer);
    vLayout->addLayout(hLayout);

    QWidget *window = new QWidget;
    window->setMinimumSize(100, 130);
    window->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    window->setLayout(vLayout);
    window->resize(300, 320);

    window->show();
    return app.exec();
}
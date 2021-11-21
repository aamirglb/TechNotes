#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>
#include "ticker.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *ticker = new Ticker;
    auto *button = new QPushButton(QWidget::tr("Update Ticker"));
    button->setDefault(true);
    auto *lineEdit = new QLineEdit;

    QObject::connect(button, &QPushButton::clicked,
            [&](){ ticker->setText(lineEdit->text() + QString(" ")); });

    auto *hLayout  = new QHBoxLayout;
    hLayout->addWidget(lineEdit);
    hLayout->addWidget(button);

    auto *vLayout = new QVBoxLayout;
    vLayout->addWidget(ticker);
    vLayout->addLayout(hLayout);

    auto *window = new QWidget;
    window->setLayout(vLayout);
    window->show();

    return app.exec();
}
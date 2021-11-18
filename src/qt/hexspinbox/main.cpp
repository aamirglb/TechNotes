#include <QApplication>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>
#include "hexspinbox.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto *hex = new HexSpinBox;
    auto *dec = new QSpinBox;
    hex->setRange(0, 0x7FFFFFFF);
    dec->setRange(0, 0x7FFFFFFF);

    auto *layout = new QGridLayout;
    layout->addWidget(new QLabel("<b>Hex: </b>"), 0, 0);
    layout->addWidget(hex, 0, 1);
    layout->addWidget(new QLabel("<b>Dec: </b>"), 1, 0);
    layout->addWidget(dec, 1, 1);

    QObject::connect(hex, QOverload<int>::of(&HexSpinBox::valueChanged), dec, &QSpinBox::setValue);
    QObject::connect(dec, QOverload<int>::of(&QSpinBox::valueChanged), hex, &HexSpinBox::setValue);

    auto *window = new QWidget;
    window->setLayout(layout);
    window->setFixedSize(window->sizeHint());
    window->show();
    return app.exec();
}

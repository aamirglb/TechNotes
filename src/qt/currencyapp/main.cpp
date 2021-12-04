#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *window = new CurrencyWidget("rates.csv");
    window->show();
    return app.exec();
}
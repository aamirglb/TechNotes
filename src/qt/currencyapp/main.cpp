#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *window = new CurrencyWidget("exchange_rates.txt");
    window->show();
    return app.exec();
}
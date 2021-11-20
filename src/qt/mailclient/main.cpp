#include <QApplication>

#include "mailclient.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MailClient *window = new MailClient;
    window->show();
    return app.exec();
}
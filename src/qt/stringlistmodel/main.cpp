#include <QApplication>

#include "dialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStringList leaders;
    leaders << "Mohammad" << "Aamir" << "Ali";
    auto *window = new TeamLeadersDialog(leaders);
    window->show();
    return app.exec();
}
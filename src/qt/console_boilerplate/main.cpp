#include <QCoreApplication>
#include <QDebug>
#include <QDate>
#include <QDateTime>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "Hello Qt!!";

    qDebug() << QDate::currentDate().toString("dd-MM-yyyy");
    qDebug() << QDateTime::currentDateTime().toString("dd-MM-yyyy");
}
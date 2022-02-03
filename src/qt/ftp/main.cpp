#include <QApplication>
#include <QFtp>
#include <QUrlInfo>
#include <QNetworkSession>
#include <QDebug>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFtp *ftp = new QFtp;
    auto debug = qDebug();
    ftp->connectToHost("127.0.0.1", 21);
    ftp->login("strio", "Strio@2021");

    QObject::connect(ftp, &QFtp::commandFinished, [&](int i, bool b) {
        qDebug() << "Command " << i << "finished. Status: " << b;
    });

    QObject::connect(ftp, &QFtp::listInfo, [&](const QUrlInfo& i){
        auto d = qDebug();
        QString entry = QString("%1 %2 %3 %4 %5 %6")
            .arg(i.isDir() ? "d" : "-", 1)
            .arg(i.name().leftJustified(50, ' '))
            .arg(QString::number(i.size()), 10)
            .arg(i.owner().leftJustified(6, ' '))
            .arg(i.group().leftJustified(6, ' '))
            .arg(i.lastModified().toString("MMM dd yyyy"));
        d.noquote();
        d << entry;
    });

    ftp->list();
    ftp->close();
    return app.exec();
    // QNetworkSession *networkSession;
    // QNetworkConfigurationManager manager;
}
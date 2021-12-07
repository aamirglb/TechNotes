#include <QCoreApplication>
#include <QImageReader>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[]) {
    QStringList args = QCoreApplication::arguments();
    QString path = QDir::currentPath();
    QString home = QDir::homePath();
    qDebug() << "Current Dir: " << path;
    qDebug() << "Home Path: " << home;

    QStringList filters;
    foreach(QByteArray format, QImageReader::supportedImageFormats())
        qDebug() << format;

    qDebug() << "Done.";
    return 0;
}
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <string>
#include <iostream>

int main(int argc, char** argv) {

    std::string h("Hello World");
    QString s = "Hello, World!!";
    qDebug() << s;
    qDebug() << QString::fromStdString(h);
    // std::cout << h << std::endl;

    //==========Minimal source code of a Qt application=====:
    QCoreApplication app(argc, argv); 

    return QCoreApplication::exec();
}
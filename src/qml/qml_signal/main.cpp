#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>

class MyClass: public QObject {
    Q_OBJECT
public slots:
    void cppSlot(const QString &msg) {
        qDebug() << "Called the C++ slot with message:" << msg;
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickView view(QUrl::fromLocalFile("../MyItem.qml"));
//    QObject *item = view.rootObject()->findChild<QObject*>("item");
    QObject *item = view.rootObject();

    if(!item)
        qDebug() << "Item is NULL";

    MyClass myClass;
    QObject::connect(item, SIGNAL(qmlSignal(QString)), &myClass, SLOT(cppSlot(QString)));

    view.show();
    return app.exec();
}

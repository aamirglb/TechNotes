#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>

#include <QVariantList>
#include <QVariantMap>
#include <QDate>

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

    QVariantList list;
    list << 10 << QColor(Qt::green) << "bottles" << 3.1425;

    QVariantMap map;
    map.insert("language", "QML");
    map.insert("released", QDate(2010, 9, 21));

    QMetaObject::invokeMethod(item, "readValues",
        Q_ARG(QVariant, QVariant::fromValue(list)),
        Q_ARG(QVariant, QVariant::fromValue(map))
    );

    MyClass myClass;
    QObject::connect(item, SIGNAL(qmlSignal(QString)), &myClass, SLOT(cppSlot(QString)));

    view.show();
    return app.exec();
}

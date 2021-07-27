#include <QtGui>
#include <QtQml>
#include <QQuickView>
#include <QByteArray>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>



#include "citymodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cities.db");
    if(!db.open()) {
        qFatal("unable to open database");
    } else {
        qDebug() << "Database opened successfully";
    }

CityModel *model = new CityModel; 
model->setTable("city"); 
model->generateRoleNames();
model->setHeaderData(0, Qt::Horizontal, "City");
model->setHeaderData(1, Qt::Horizontal, "Country");
model->select(); 


    // QSqlTableModel *m_model = new QSqlTableModel();
    // m_model->setTable("city");
    // m_model->setHeaderData(0, Qt::Horizontal, "Capital");
    // m_model->setHeaderData(1, Qt::Horizontal, "Country");
    // // m_view->setModel(m_model);
    // m_model->select();
    // qDebug() << m_model->record(0).value("city").toString();
    // qDebug() << m_model->record(1).value("city").toString();
    

    // QHash<int, QByteArray> roles;
    // roles[Qt::UserRole+1] = "city";
    // roles[Qt::UserRole+2] = "country";
    // m_model->setRoleNames(roles);

    QQuickView view;
    view.rootContext()->setContextProperty("cityModel", model);
    // view.setSource(QUrl("qrc:/qml/main.qml"));
    QUrl source = QUrl::fromLocalFile("main.qml");
    view.setSource(source);
    
    view.show();
    return app.exec();
}

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>

const QString DB_NAME("capital_cities.db");
QStringList TableHeader;

bool createDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_NAME);
    if(!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
            db.lastError().text());
        return false;
    }
    return true;
}

bool createTable() {

    // check if table already created
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM capital_city;");
    checkQuery.exec();
    if (checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        qDebug() << "Database Table has" << count << "entries";
        return true;
    }

    // Open the capital city CSV file
    QFile file(":/capital_cities.csv");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, QObject::tr("Open Error"),
            QString("Unable to open %1").arg(file.fileName()));
        return false;
    }
    
    QSqlQuery query("CREATE TABLE capital_city ("
            "country TEXT CHECK( country != ''), "
            "capital TEXT CHECK( capital != ''));");

    QTextStream in(&file);
    auto count {0};
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if(fields.size() >= 2) {
            if(count == 0) {
                TableHeader << fields[0] << fields[1];
                ++count;
                continue;
            }
            qDebug() << count++ << fields[0] << "\t" << fields[1];
            QSqlQuery query;
            query.prepare("INSERT INTO capital_city (country, capital) "
                  "VALUES (:country, :capital)");
            query.bindValue(":country", fields[0]);
            query.bindValue(":capital", fields[1]);
            query.exec();

            if (!query.isActive())
                QMessageBox::warning(nullptr, QObject::tr("Database Error"), query.lastError().text());
        }
    }
    return true;
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    if(!createDatabase())
        return 1;

    if(!createTable())
        return 1;

    qDebug() << "Database: " << DB_NAME;

    auto *model = new QSqlTableModel;
    model->setTable("capital_city");
    for(auto i = 0; i < TableHeader.size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, TableHeader[i]);
    model->select();

    auto *view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);

    view->setMinimumSize(600, 800);
    view->show();
    return app.exec();
}
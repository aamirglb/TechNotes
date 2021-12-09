#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDriver>

#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QTableView>
#include <QHeaderView>

#include <QWidget>
#include <QComboBox>
#include <QLayout>
#include <QLabel>

const QString DB_NAME("capital_cities.db");
QStringList TableHeader;
QSqlTableModel *model;
QLabel *rowCntLabel;

void updateFilter(int index, QString column) {
    if(index != 0) {
        QChar c = 'A' + index - 1;
        QString pattern = QString("%1").arg(c);
        qDebug() << "Setting pattern to " << QString("%1 LIKE '%2%'").arg(column).arg(pattern);
        model->setFilter(QString("%1 LIKE '%2%'").arg(column).arg(pattern));
    } else {
        model->setFilter("");
    }
    model->select();
    rowCntLabel->setText(QString("<b>%1</b>").arg(model->rowCount()));
}

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
            query.prepare("INSERT INTO capital_city (capital, country) "
                  "VALUES (:capital, :country)");
            query.bindValue(":capital", fields[0]);
            query.bindValue(":country", fields[1]);
            query.exec();

            if (!query.isActive())
                QMessageBox::warning(nullptr, QObject::tr("Database Error"), query.lastError().text());
        }
    }
    return true;
}

QWidget* createGUI() {
    QWidget *window = new QWidget;

    auto *gridLayout = new QGridLayout;
    auto *countryCBox = new QComboBox;
    auto *capitalCBox = new QComboBox;
    rowCntLabel = new QLabel("");

    QStringList letters;
    letters << QString("All");
    for(auto c = 'A'; c <= 'Z'; ++c)
        letters << QString("%1").arg(c);
    
    countryCBox->setInsertPolicy(QComboBox::NoInsert);
    countryCBox->addItems(letters);

    capitalCBox->setInsertPolicy(QComboBox::NoInsert);
    capitalCBox->addItems(letters);

    gridLayout->addWidget(new QLabel(QObject::tr("<b>Country: </b>")), 0, 0);
    gridLayout->addWidget(countryCBox, 0, 1);
    gridLayout->addWidget(new QLabel(QObject::tr("<b>Capital: </b>")), 0, 2);
    gridLayout->addWidget(capitalCBox, 0, 3);
    gridLayout->addWidget(new QLabel(QObject::tr("<b>Row Count: </b>")), 1, 0);
    gridLayout->addWidget(rowCntLabel, 1, 1);

    // auto *model = new QSqlTableModel;
    model = new QSqlTableModel;
    model->setTable("capital_city");
    for(auto i = 0; i < TableHeader.size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, TableHeader[i]);
    // model->setFilter("country LIKE 'B%'");
    model->select();
    rowCntLabel->setText(QString("<b>%1</b>").arg(model->rowCount()));

    auto *view = new QTableView;
    view->setModel(model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(view);
    window->setLayout(mainLayout);
    window->setMinimumSize(600, 400);

    QObject::connect(countryCBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [&](int index){ updateFilter(index, "country"); });
    
    QObject::connect(capitalCBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [&](int index){ updateFilter(index, "capital"); });

    return window;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    if(!createDatabase())
        return 1;

    if(!createTable())
        return 1;

    qDebug() << "Database: " << DB_NAME;
    QSqlDriver *driver = QSqlDatabase::database().driver();
    if(driver->hasFeature(QSqlDriver::Transactions))
        qDebug() << "Database support transactions";

    if(driver->hasFeature(QSqlDriver::BLOB))
        qDebug() << "Database support BLOB";
    
    if(driver->hasFeature(QSqlDriver::Unicode))
        qDebug() << "Database support Unicode";

    auto *window = createGUI();
    window->show();
    return app.exec();
}
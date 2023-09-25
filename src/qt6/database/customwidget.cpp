#include "customwidget.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QDebug>

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Chinook_Sqlite.sqlite");

    if(!db.open()) {
        qDebug() << "Unable to open database";
    } else {
        qDebug() << "Database opened successfully";
    }

    // select all table names from the database
    QSqlQueryModel model;
    model.setQuery("SELECT name FROM sqlite_master WHERE type='table'");

    m_tableNames = new QComboBox(this);
    for(int i = 0; i < model.rowCount(); ++i) {
        m_tableNames->addItem(model.record(i).value("name").toString());
    }
    connect(m_tableNames, &QComboBox::currentIndexChanged, this, &CustomWidget::indexChanged);

    m_model = new QSqlTableModel(this);
    m_view = new QTableView(this);
    m_view->setModel(m_model);

    // m_proxy = new QSortFilterProxyModel(this);
    // m_proxy->setSourceModel(m_model);
    // m_view->setModel(m_proxy);
    m_view->setSortingEnabled(true);

    QHBoxLayout *row = new QHBoxLayout;
    row->addWidget(new QLabel("Select Table: "));
    row->addWidget(m_tableNames);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(row);
    layout->addWidget(m_view);
    this->setLayout(layout);

    m_tableNames->setCurrentIndex(1);
}

void CustomWidget::indexChanged(int index)
{
    m_model->clear();
    m_model->setTable(m_tableNames->currentText());

    QString query = QString("SELECT name FROM PRAGMA_TABLE_INFO('%1')").arg(m_tableNames->currentText());
    QSqlQueryModel model;
    model.setQuery(query);

    for(int i = 0; i < model.rowCount(); ++i) {
        m_model->setHeaderData(i, Qt::Horizontal,model.record(i).value("name").toString());
        qDebug() << model.record(i).value("name").toString();
    }

    m_view->setModel(m_model);
    m_model->select();

    qDebug() << m_tableNames->currentText() << " table selected.";
}
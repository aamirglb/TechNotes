#include "widget.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

CurrencyWidget::CurrencyWidget(QString filename, QWidget *parent)
    : QWidget(parent) {

    qDebug() << filename;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        while(!in.atEnd()) {
            auto line = in.readLine();
            auto fields = line.split(",");
            currencyMap.insert(fields[2], fields[1].toDouble());
            countryMap.insert(fields[2], fields[0]);
        }
        file.close();
    } else {
        QMessageBox::information(nullptr, "Error", file.errorString());
        currencyMap.insert("AUD", 1.3259);
        currencyMap.insert("CHF", 1.2970);
        currencyMap.insert("SGD", 1.6901);
        currencyMap.insert("USD", 1.0000);

        countryMap.insert("AUD", "AUSTRALIA");
        countryMap.insert("CHF", "SWITZERLAND");
        countryMap.insert("SGD", "SINGAPORE");
        countryMap.insert("USD", "UNITED STATES");
    }
    
    currencyModel.setCurrencyMap(currencyMap, countryMap);

    tableView = new QTableView;
    tableView->setModel(&currencyModel);
    tableView->setAlternatingRowColors(true);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tableView);
    setLayout(mainLayout);
    setMinimumSize(1200, 500);
}
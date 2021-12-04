#include "currencymodel.h"
#include <QAbstractItemModel>

CurrencyModel::CurrencyModel(QObject *parent)
    : QAbstractTableModel(parent) {
}

int CurrencyModel::rowCount(const QModelIndex & /* parent */) const {
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex & /* parent */) const {
    return currencyMap.count();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
        return QVariant();

    if(role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if(role == Qt::DisplayRole) {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());

        if(currencyMap.value(rowCurrency) == 0.0)
            return "####";

        double amount = currencyMap.value(columnCurrency)
                        / currencyMap.value(rowCurrency);

        return QString("%1").arg(amount, 0, 'f', 4);
    }
    return QVariant();
}

QVariant CurrencyModel::headerData(int section, 
                                    Qt::Orientation orientation,
                                    int role) const {
    if(role == Qt::ToolTipRole) {
        return countryAt(section);
    } else if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal)
            return QString("%1\n(%2)").arg(currencyAt(section)).arg(countryAt(section));
        else
            return currencyAt(section);
    } else {
        return QVariant();
    }
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map, const QMap<QString, QString> &countries) {
    beginResetModel();
    currencyMap.clear();
    countryNames.clear();
    
    currencyMap = map;
    countryNames = countries;

    endResetModel();
}

QString CurrencyModel::currencyAt(int offset) const {
    return (currencyMap.begin() + offset).key();
}

QString CurrencyModel::countryAt(int offset) const {
    return (countryNames.begin() + offset).value();
}


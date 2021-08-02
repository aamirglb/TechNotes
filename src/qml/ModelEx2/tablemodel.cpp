#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return 200;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 200;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
            return QString("%1, %2").arg(index.column()).arg(index.row());
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

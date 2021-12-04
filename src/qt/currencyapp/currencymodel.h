#include <QAbstractTableModel>
#include <QMap>

class CurrencyModel : public QAbstractTableModel {
public:
    CurrencyModel(QObject *parent = nullptr);

    void setCurrencyMap(const QMap<QString, double> &map);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, 
            int role) const;
        
private:
    QString currencyAt(int offset) const;
    QMap<QString, double> currencyMap;
};


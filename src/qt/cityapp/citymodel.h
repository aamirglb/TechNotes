#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>

class CityModel : public QAbstractTableModel {
    Q_OBJECT
public:
    CityModel(QObject *parent = nullptr);

    void setCities(const QStringList &cityNames);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    int offsetOf(int row, int column) const;

    QStringList cities;
    QVector<int> distances;
};
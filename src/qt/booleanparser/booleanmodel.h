#include <QAbstractItemModel>

class BooleanModel : public QAbstractItemModel {
public:
    BooleanModel(QObject *parent = nullptr);
    ~BooleanModel();

    void setRootNode(Node *node);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    Node *nodeFromIndex(const QModelIndex &index) const;
    Node *rootNode;
};

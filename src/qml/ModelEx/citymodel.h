#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QByteArray>

#include <QDebug>

class CityModel : public QSqlRelationalTableModel
{
    Q_OBJECT 
private : 
    QHash<int, QByteArray> roles;

public:
    CityModel(QObject *parent = 0) : QSqlRelationalTableModel(parent) {
    }
    virtual ~CityModel() {
    }

public:
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
        if (index.row() >= rowCount()) {
            return QString("");
        }

        if (role < Qt::UserRole) {
            return QSqlQueryModel::data(index, role);
        } else { 
            // search for relationships 
            for (int i = 0; i < columnCount(); ++i) { 
                if (this->relation(i).isValid()) { 
                    return record(index.row()).value(QString(roles.value(role)));
                } 
            } 
            // if no valid relationship was found 
            return QSqlQueryModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole); 
        }
    }

    void generateRoleNames() {
        roles.clear(); 
        int nbCols = this->columnCount(); 
        qDebug() << "Generating User Roles: Column Count: " << nbCols;
        for (int i = 0; i < nbCols; ++i) { 
            qDebug() << this->headerData(i, Qt::Horizontal).toString();
            roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray(); 
        }
        // setRoleNames(roles);
    }

    virtual QHash<int, QByteArray> roleNames() const {
        return roles;
    }
};
#include <QWidget>
#include "currencymodel.h"

class QTableView;

class CurrencyWidget : public QWidget {
public:
    CurrencyWidget(QString filename, QWidget *parent = nullptr);

private:
    QMap<QString, double> currencyMap;
    QMap<QString, QString> countryMap;
    QTableView *tableView;
    CurrencyModel currencyModel;
};
#include <QApplication>
#include <QTableView>
#include "citymodel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QStringList cities;

    cities << "Arvika" << "Boden" << "Eskilstuna" << "Falun"
            << "Filipstad" << "Halmstad" << "Helsingborg" << "Karlstad"
            << "Kiruna" << "Kramfors" << "Motala" << "Sandviken"
            << "Skara" << "Stockholm" << "Sundsvall" << "Trelleborg";

    CityModel cityModel;
    cityModel.setCities(cities);

    QTableView tableView;
    tableView.setModel(&cityModel);
    tableView.setAlternatingRowColors(true);
    tableView.setMinimumSize(1200, 500);
    tableView.show();

    return app.exec();
}
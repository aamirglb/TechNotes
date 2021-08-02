import QtQuick 2.12
import Qt.labs.qmlmodels 1.0

Rectangle {
    width: 800; height: 800
    color: "#19232D"

    TableView {
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: TableModel {
            TableModelColumn { display: "name" }
            TableModelColumn { display: "color" }
        }
    }


}

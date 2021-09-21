import QtQuick          2.12
import QtLocation       5.12
import QtPositioning    5.12
import QtQuick.Controls 2.12

MapItemGroup {
    id: itemGroup
    property alias polyline: mainPolyline
    property alias text: distText.text
    property alias textCoordinate: distText.coordinate

    MapPolyline {
        property alias mainPolyline: mainPolyline
        id: mainPolyline
        line.width: 2
        line.color: 'green'
    }

    MapQuickItem {
        id: distText
        property alias text: txtLabel.text
        sourceItem: Label {
            id: txtLabel
            text: distText.text
            font.bold: false
            font.pixelSize: 11
            color: "black"
        }
    }
}

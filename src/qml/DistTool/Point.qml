import QtQuick          2.12
import QtLocation       5.12
import QtPositioning    5.12
import QtQuick.Controls 2.12

MapItemGroup {
    id: itemGroup
    property alias coordinate:  point.coordinate

    MapQuickItem {
        id:  point
        sourceItem: Rectangle {
            width: 12; height: 12; radius: 6
            color: "green"
            border.width: 1;
            border.color: "white"
            smooth: true
        }
        anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
    }
}

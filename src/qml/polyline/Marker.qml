import QtQuick          2.12                                                                                                                                                  
import QtQuick.Window   2.12
import QtLocation       5.6
import QtPositioning    5.6
import QtQuick.Controls 2.5

MapQuickItem {

    property alias marker: marker

    id: marker
    sourceItem: Rectangle {
        width: 10
        height: 10
        color: "red"
        smooth: true
        radius: 15
    }
    opacity: 1.0
    anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
}

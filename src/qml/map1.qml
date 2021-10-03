import QtQuick          2.12
import QtLocation       5.12
import QtPositioning    5.12

Item {
    width: 400; height: 400

    Rectangle {
//        anchors.centerIn: parent
        anchors.fill: parent
//        width: 300; height: 300

        Plugin {
            id: mapPlugin
            name: "esri"
        }

        Map {
            id:             mapItem
            anchors.fill:   parent
            plugin:         mapPlugin
            center:         QtPositioning.coordinate(59.91, 10.75)
            zoomLevel:      15
        }
    }
}

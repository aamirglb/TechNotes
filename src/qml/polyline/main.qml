import QtQuick          2.12                                                                                                                                                  
import QtQuick.Window   2.12
import QtLocation       5.6
import QtPositioning    5.6
import QtQuick.Controls 2.5
import "componentCreation.js" as MyScript

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480

    // This property indicates the mode, if changeMode=0 is a polyline,
    // if changeMode=OtherNumber is an array or single lines
    property int changeMode: 1

    Plugin {
        id: osmMapPlugin
        name: "osm"
    }

    Map {
        id: themap
        anchors.fill: parent
        zoomLevel: 12
        plugin: osmMapPlugin
        center: QtPositioning.coordinate(-34.171634, -70.734406)
    }

    MouseArea{
        anchors.fill: parent
        z:1
        onClicked: {
            MyScript.createElements(Qt.point(mouse.x,mouse.y))
        }
    }
}

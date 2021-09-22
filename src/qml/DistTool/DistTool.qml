import QtQuick          2.12
import QtQuick.Window   2.12
import QtLocation       5.6
import QtPositioning    5.6
import QtQuick.Controls 2.5

Window {
    id:         _root
    width:      Qt.platform.os == "android" ? Screen.width : 768
    height:     Qt.platform.os == "android" ? Screen.height : 768
    visible:    true

    // 0 - Normal, 1 - Distance Measurement Mode
    property var appMode:  0
    property string mouseClickText: ""
    property bool clickInfoVisible: false
    property var centerLocation: QtPositioning.coordinate(59.91, 10.75)
    property var firstPoint: undefined
    property int clickCount: 0


    function addPoint(lat, lon) {
        let comp = Qt.createComponent("Point.qml")
        if( comp.status !== Component.Ready ) {
            console.log("Component Not Ready");
            if( comp.status === Component.Error )
                console.debug("Error:"+ comp.errorString() );
            return;
        }

        // Create object dynamically
        let target = comp.createObject(_root, { coordinate: QtPositioning.coordinate(lat, lon) });
        mapItem.addMapItemGroup(target)

        if(clickCount == 2) {
            let comp = Qt.createComponent("Line.qml");
            if (comp.status === Component.Ready) {
                var line = comp.createObject(mapItem);
                var secondPoint = QtPositioning.coordinate(lat, lon);
                line.polyline.addCoordinate(firstPoint)
                line.polyline.addCoordinate(secondPoint);
                mapItem.addMapItemGroup(line);

                // distance calculation
                var distance = firstPoint.distanceTo(secondPoint)
                var dst = ''
                if( distance > 1000 ) {
                    dst = (distance / 1000)
                    dst = dst.toFixed(2) + ' km'
                }
                else {
                    dst = distance.toFixed(0) + ' m'
                }

                let azimuth = firstPoint.azimuthTo(secondPoint);
                let halfDistance = distance / 2;
                line.textCoordinate = firstPoint.atDistanceAndAzimuth(halfDistance, azimuth)
                line.text = dst
            }
        }
    }

    Plugin {
        id: mapPlugin
        name: "esri"
    }

    Map {
        id:             mapItem
        anchors.fill:   parent
        plugin:         mapPlugin
        center:         centerLocation // Oslo
        zoomLevel:      15


    }

    Timer {
        id:         timer
        running:    false
        repeat:     false
        interval:   5000
        onTriggered: { clickInfoVisible = false; }
    }


    Rectangle {
        id: clickInfo
        width: 120
        height: 30
        visible: clickInfoVisible

        color: "#80220000"
        border.color: "black"

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Text {
            text: qsTr(mouseClickText)
            color: "white"
            anchors.centerIn: parent
            font.pointSize: 12
        }
    }

    Rectangle {
        width: 180
        height: 30
        color: "#80220000"
        border.color: "black"

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            property var status: appMode ? "ON" : "OFF"
            text: qsTr("Distance Mode: " + status)
            color: "white"
            anchors.centerIn: parent
            font.pointSize: 12
        }
    }

     Loader {
         id: pageLoader
         anchors.fill: parent
     }

    MouseArea {
        id:                 mouseArea
        anchors.fill:       parent
        acceptedButtons:    Qt.RightButton | Qt.LeftButton
        propagateComposedEvents: true
        onClicked: {

            if(mouse.button === Qt.RightButton) {
                mouseClickText = "Right Click"
                if(appMode === 0) contextMenu.popup();
                if(appMode === 1) appMode = 0;
            }

            if(mouse.button === Qt.LeftButton) {
                mouseClickText = "Left Click"
                // create a point
                if(appMode === 1) {
                    let lat = mapItem.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude
                    let lon = mapItem.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude

                    if(clickCount === 0) {
                        firstPoint = QtPositioning.coordinate(lat, lon);
                    }
                    ++clickCount;
                    addPoint(lat, lon);

                    if(clickCount == 2) {
                        firstPoint = undefined;
                        clickCount = 0;
                    }
                }
            }

            if(timer.running) timer.running = false
            clickInfoVisible = true
            timer.running = true;
        }

        Menu {
            id: contextMenu
            Action {
                id:     addTarget
                text:   qsTr("Dist Tool")
                onTriggered: {
                    if(!appMode) appMode = 1;

                }
            }
        }
    }
}

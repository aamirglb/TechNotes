// SquareButton.qml
import QtQuick 2.12

Rectangle {
    id: root

    signal activated(real xPosition, real yPosition)
    property point mouseXY
    property int side: 600
    width: side; height: side

    MouseArea {
        id: area
        anchors.fill: parent
        onClicked: {
            root.activated(mouse.x, mouse.y)
        }
    }

    Connections {
        target: root
        onActivated: {
            console.log("onActivated: (", xPosition, ", ", yPosition, ")")
        }
    }
    // TapHandler {
    //     id: handler
    //     onTapped: root.activated(mouseXY.x, mouseXY.y)
    //     onPressedChanged: mouseXY = handler.point.position
    // }
}
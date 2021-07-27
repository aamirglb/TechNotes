import QtQuick 2.12

Rectangle {
    id: root
    width: 400; height: 400
    color: "#3c3c3c"
    property int gridCellWidth: 40

    Repeater {
        id: hLines
        model: root.height / gridCellWidth
        delegate: Rectangle {
            width: root.width
            height: 1
            color: "white"
            y: index * gridCellWidth
            x: 0
        }
    }

    Repeater {
        id: vLines
        model: root.width / gridCellWidth
        delegate: Rectangle {
            width: 1
            height: root.height
            x: index * gridCellWidth
            y: 0
        }
    }

    Rectangle {
        id: rect
        width: 80; height: 80
        color: "darkgreen"
        border.color: Qt.lighter(color)
//        anchors.centerIn: parent

        Rectangle {
            width: 10; height: 10; radius: 5
            color: "red"
            x: 10; y:10
        }

        Behavior on rotation {
            NumberAnimation {
                duration: 1000
                alwaysRunToEnd: true
            }
        }

        Behavior on x {
            NumberAnimation {
                duration: 1000
                alwaysRunToEnd: true
            }
        }

        Behavior on y {
            NumberAnimation {
                duration: 1000
                alwaysRunToEnd: true
            }
        }
    }

    focus: true
    Keys.onSpacePressed: {
        rect.rotation += 90
    }

    Keys.onRightPressed: {
        if(rect.x + (gridCellWidth*2) <= root.width)
            rect.x += gridCellWidth
    }

    Keys.onLeftPressed: {
        if(rect.x - gridCellWidth >= 0)
            rect.x -= gridCellWidth
    }

    Keys.onUpPressed: {
        rect.y -= gridCellWidth
    }

    Keys.onDownPressed: {
        rect.y += gridCellWidth
    }

    Keys.onEscapePressed: {
        rect.x = 0;
        rect.y = 0;
        rect.rotation = 0
    }

    MouseArea {
        anchors.fill: parent
        onClicked: rect.rotation += 90
    }
}

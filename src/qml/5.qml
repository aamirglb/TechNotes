import QtQuick 2.12

Rectangle {
    id: root
    property bool pressed: false
    width: 400; height: 600
    color: "#3c3c3c"

    Rectangle {
        id: greenBox
        width: 48; height: 48
        color: "green"
        x: 40; y: root.height-height
        NumberAnimation on y {
            to: 40; duration: 4000
            running: root.pressed
        }
    }

    Rectangle {
        id: blueBox
        width: 48; height: 48
        color: "blue"
        x: (root.width - width)/2; y: root.height - height
        Behavior on y {
            NumberAnimation { duration: 4000 }
        }
    }

    MouseArea {
        id: area
        anchors.fill: parent
        onPressed:  {
            root.pressed = true;
            blueBox.y = 40 + Math.random() * (250-40);
        }
        onReleased: {
                root.pressed = false;
                blueBox.y = 40;
                greenBox.y = root.height - greenBox.height
            }
    }


}

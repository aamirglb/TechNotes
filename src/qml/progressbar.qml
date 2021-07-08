import QtQuick 2.0
import QtQuick.Layouts 1.12

Rectangle {
    id: root
    width: 125
    height: 40
    property bool running: false
    property bool shrink: false

    Rectangle {
        id: child
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        property int t: bar.width
        width: 100; height: 20
        Text {
            anchors.centerIn: parent
            text: child.t.toString()
            color: "black"
            z: 100
        }

        Rectangle {
            id: bar
            width: 100
            height: 20
            anchors.left: parent.left
            anchors.top: parent.top
            color: "green"
            NumberAnimation on width {

                        to: shrink ? 0 : 100
                        duration: 2000
                        running: root.running
                    }

    }


        focus: true
        Keys.onSpacePressed: {
            if(root.running) root.running = false;
            shrink = !shrink
            console.log("shrink: ", shrink);
            root.running = true
        }

    }
}



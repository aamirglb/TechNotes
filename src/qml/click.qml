import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: rect
    width: 250; height: 250

    Button {
        id: button
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Change Color!"
        // onClicked: {
        //     rect.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        // }
    }

    Connections {
        target: button
        onClicked: {
            console.log("clicked")
            rect.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
        }
    }
}
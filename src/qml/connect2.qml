import QtQuick 2.12

Rectangle {
    id: forwarder
    width: 100; height: 100

    signal send()
    onSend: console.log("Send clicked")

    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: console.log("Mouse clicked")
    }

    Component.onCompleted: {
        mousearea.clicked.connect(send)
    }
}
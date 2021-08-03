import QtQuick 2.12

Item {
    id: item
    width: 100; height: 100

    property int clickCount: 0
    signal qmlSignal(string msg)

    Rectangle {
        width: 80; height: 80
        anchors.centerIn: parent
        color: 'black'
        Text {
            anchors.centerIn: parent
            text: qsTr("%1".arg(clickCount))
            color: 'white'
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ++clickCount;
            item.qmlSignal("Item Clicked %1 times".arg(clickCount))
        }
    }
}

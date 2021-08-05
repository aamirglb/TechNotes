import QtQuick 2.12

Item {
    id: item
    width: 100; height: 100

    property int clickCount: 0
    signal qmlSignal(string msg)

    function readValues(anArray, anObject) {
        for(var i=0; i<anArray.length; ++i)
            console.log("Array Item:", anArray[i])

        for(var prop in anObject) {
            console.log("Object Item:", prop, "=", anObject[prop])
        }
    }
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

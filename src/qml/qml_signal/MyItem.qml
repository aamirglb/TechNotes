import QtQuick 2.12

Item {
    id: item
    width: 100; height: 100
    property var _background: ['black', 'green', 'red', 'blue', 'gray', 'steelblue']
    property int _color_idx: 0

    property int clickCount: 0
    signal qmlSignal(string msg)

    function readValues(anArray, anObject) {
        for(var i=0; i<anArray.length; ++i)
            console.log("Array Item:", anArray[i])

        for(var prop in anObject) {
            console.log("Object Item:", prop, "=", anObject[prop])
        }
    }

    function readDate(dt) {
        console.log("The given date is:", dt.toUTCString());
        return new Date();
    }
    Rectangle {
        width: 80; height: 80
        anchors.centerIn: parent
        color: _background[_color_idx]
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
            _color_idx = Math.floor(Math.random() * 6)
            item.qmlSignal("Item Clicked %1 times".arg(clickCount))
        }
    }
}

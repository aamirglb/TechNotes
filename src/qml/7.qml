import QtQuick 2.5
import QtQuick.Layouts 1.2

Rectangle {
    id: root
    width: 800
    height: 600
    property int duration: 8*1000

    ListModel {
        id: posModel
        ListElement { xPos: 10; yPos: 10 }
        ListElement { xPos: 30; yPos: 30 }
        ListElement { xPos: 50; yPos: 50 }
    }

    ListView {
        model: posModel
        anchors.fill: parent
        delegate: Rectangle {
            width: 10; height: 10; radius: 5;
            color: "red"
            x: xPos; y: yPos; z: 100
            Component.onCompleted: {
                console.log("creating rect at: ", x, y)
            }
        }
    }
}

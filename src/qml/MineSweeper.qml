import QtQuick 2.0
import QtQuick.Layouts 1.12
Rectangle {
    width: (80*10)+80
    height: (50*10)+60
//    color: "#ECE9D6"
    color: "white"

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 10
        Layout.rowSpan: 1
        Layout.columnSpan: 1
        Repeater {
            model: 100
            Rectangle {
                width: 80
                height: 50
                color: "lightgray"
                border.color: "black"
                Text {
                    anchors.centerIn: parent
                    text: qsTr(index.toString())
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(index, " clicked.");
                    }
                }
            }
        }
    }
}

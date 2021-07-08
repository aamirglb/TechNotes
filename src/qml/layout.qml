import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.2

Rectangle {
    width: 200
    height: 200

    GridLayout {
        rows: 4
        columns: 1
        Repeater {
            model: 4
            delegate: Row { spacing: 4
                Label { text: "V-1 CC: ";  }
                Label { text: "Connected";   }
            }
        }
    }



//    Rectangle {
//        id: _root
//        anchors.centerIn: parent
//        width: column.width + 3
//        height: column.height + 2
//        border.color: "black"
//        border.width: 1

//        Column {
//            id: column
//            spacing: 2
////            width: Math.max(layout.width, label.width)
//            width: 100
//            height: 150
//            anchors.margins: 1
//            anchors.centerIn: parent

//            Label {
//                id: label
//                text: "Health Status"
//                font.underline: true
//                anchors.horizontalCenter: parent.horizontalCenter
//            }

//            GridLayout {
//                id: layout
//                anchors.margins: 1
//                width: parent.width
//                height:parent.height
////                columns: 2
////                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.fill: parent

//                Repeater {
//                    model: 2
////                    Layout.alignment: Qt.AlignVCenter
//                    delegate: Item {
//                        Label { text: "V-1 CC: " }
//                        Label { text: "Connected" }
//                    }
//                }

////                Label { text: "V-1 CC: " }
////                Label { text: "Connected" }

////                Label { text: "V-2 CC: " }
////                Label { text: "Connected" }
//            }

//        }
//    }
}



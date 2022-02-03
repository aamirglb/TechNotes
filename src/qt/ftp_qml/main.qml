import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    //title of the application
    title: qsTr("FTP Client")
    width: 640
    height: 480
    visible: true

    property int _textEditWidth: 120
    //    Rectangle {
    //        anchors.fill: parent
    //        color: "#3c3c3c"
    //    }


    //    menuBar: MenuBar {
    //        Menu {
    //            title: qsTr("File")
    //            MenuItem {
    //                text: qsTr("&Open")
    //                onTriggered: console.log("Open action triggered");
    //            }
    //            MenuItem {
    //                text: qsTr("Exit")
    //                onTriggered: Qt.quit();
    //            }
    //        }
    //    }

    //Content Area

    //a button in the middle of the content area
    GridLayout {
        id: mainGrid
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 8
        columns: 2

        Label {
            text: qsTr("Server: ")
        }

        Row {
            spacing: 5
//            Rectangle {
//                width: 96; height: input.height + 8
//                color: "lightsteelblue"
//                border.color: "gray"

//                property alias text: input.text
//                property alias input: input

//                TextInput {
//                    id: input
//                    anchors.fill: parent
//                    anchors.margins: 4
//                    focus: true
//                    text: ""
//                }
//            }
//            TextInput {
//                id: serverName
//                text: "192.168.168.111"
//                cursorVisible: false
//            }

            Rectangle {
                id: serverName
                width: _textEditWidth
                height: 22
                border.color: "black"
                border.width: 1

                TextEdit {
                    anchors.fill: parent
                    anchors.centerIn: parent
                    cursorVisible: true
                }
            }

            Button {
                width: _textEditWidth * .8
                height: 22
                text: qsTr("Connect")
            }

        }


        Label {
            text: qsTr("User Name: ")
        }

        Rectangle {
            id: userName
            width: _textEditWidth
            height: 22

            border.color: "black"
            border.width: 1

            TextEdit {
                anchors.fill: parent
            }
        }

        Label {
            text: qsTr("Password: ")
        }

        Rectangle {
            id: password
            width: _textEditWidth
            height: 22

            border.color: "black"
            border.width: 1

            TextEdit {
                anchors.fill: parent
            }
        }
    }

    Rectangle {
        anchors.top: mainGrid.bottom
        anchors.left: parent.left
        anchors.margins: 8
        width: mainGrid.width * 2
        height: 300

        border.color: "black"
    }

    Component.onCompleted: {
        console.log("Application loaded");
    }
}

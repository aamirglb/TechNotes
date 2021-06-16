import QtQuick 2.0

Rectangle {
    id: root
    width: 200
    height: 200
    color: "#19232D"
    property int percent: 100
    property string _fillColor: (percent > 50) ? "lime" : ((percent > 20) ? "orange" : "red")

    Timer {
        id: timer
        interval: 200; running: true; repeat: true
        onTriggered: if(percent > 0) {
                         --percent;
                     }
    }


    Rectangle {
        id: body
        anchors.centerIn: parent
        width: 100
        height: width * .4
        radius: 8
        color: parent.color
        border.color: "white"
        border.width: 1
    }

    Rectangle {
        id: head
        anchors.left: body.right
        anchors.verticalCenter: body.verticalCenter
        anchors.leftMargin: -1
        width: 6
        height: 20
        radius: 2
        color: "white"
//        border.color: "white"
//        border.width: 1
    }

    Rectangle {
        id: leftfill
        anchors.left: body.left
        anchors.top: body.top
        anchors.margins: 2
        width: (percent < 8) ? percent : 16
        height: body.height - 4
        radius: 8
        color: _fillColor
    }

    Rectangle {
        id: mainfill
        anchors.left: leftfill.right
        anchors.top: leftfill.top
        anchors.leftMargin: -8
        height: body.height - 4
        width: percent - 18
        color: _fillColor

    }

    Rectangle {
        id: rightfill
        anchors.left: body.left
        anchors.top: body.top
        anchors.topMargin: 2
        anchors.leftMargin: body.width - 16
        width: (percent > 86) ? 16-(100 - percent) : 0
        height: body.height - 4
        radius: 8
        color: _fillColor
    }

    Text {
        text: qsTr(percent.toString()) + "%"
        anchors.top: body.bottom
        anchors.horizontalCenter: body.horizontalCenter
        anchors.topMargin: 2
        color: _fillColor
    }

//    Row {
//        spacing: 1
//        anchors.fill: body
//        anchors.margins: 2

//        Repeater {
//            model: percent/10
//            delegate:
//                Rectangle {
//                    id: fillRect
////                    anchors.left: body.left
////                    anchors.leftMargin: 2
////                    anchors.top: body.top
////                    anchors.topMargin: 2
//                    height: body.height - 4
//                    width: 10
//                    color: "lime"
//                    radius: index > 0 ? 2: 8
//                }
//        }
//    }
}


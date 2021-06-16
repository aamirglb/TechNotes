import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    id: root
    width: 400
    height: 400
    color: "#19232D"

    property string _outlineColor: "white"
    property int _percent: 16
    property string _fillColor: (_percent > 50) ? "lime" : ((_percent > 20) ? "orange" : "red")
    property int _topMargin: 2

    SpinBox {
        from: 0
        to: 100
        value: 20
        onValueChanged: _percent = value
        Component.onCompleted: _percent = value
    }

    Timer {
        id: timer
        interval: 200; running: false; repeat: true
        onTriggered: {
            if(_percent > 0) {
                         --_percent;
                     }

        console.log(mainFill.width)
        }
    }

    Rectangle {
        id: battery
        anchors.centerIn: parent

        width: 50
        height: width * .4
        radius: width * .1
        color: root.color
        border.color: _outlineColor
        border.width: 2

    }

    Rectangle {
        id: terminal
        anchors.left: battery.right
        anchors.leftMargin: -1
        anchors.verticalCenter: battery.verticalCenter
        width: battery.width * .08
        height: battery.height * .4
        radius: width * .3
        color: _outlineColor
    }

    Rectangle {
        id: leftFill
        anchors.left: battery.left
        anchors.leftMargin: 2
        anchors.verticalCenter: battery.verticalCenter
        width: (_percent > 3) ? ((_percent > 5) ? ((_percent > 8) ? (battery.radius * 2) : (battery.width * .15)) : (battery.width * .05)) : 4
        height: (_percent > 0) ? (( _percent > 8) ? (battery.height - (_topMargin * 2)) : (_percent > 10) ? (battery.height * .8) : (battery.height * .7)) : 0
        radius: width/2

        color: _fillColor
        visible: false
    }

    Rectangle {
        id: rightFill
        anchors.left: battery.left
        anchors.leftMargin: mainFill.width
        anchors.top: battery.top
        anchors.topMargin: _topMargin
        width: (_percent > 85) ? ((_percent > 90) ? ((_percent > 95) ? battery.radius * 2 : battery.radius * 1.3) : battery.radius * 1.0) : 0
//        width: battery.radius * 2
        height: battery.height - (_topMargin * 2)
        radius: battery.radius
        color: _fillColor
    }

    Rectangle {
        id: mainFill
        anchors.left: battery.left
        anchors.leftMargin: leftFill.width/2
        anchors.top: battery.top
        anchors.topMargin: _topMargin

//        width: battery.width - leftFill.width
        width: (_percent > 86) ? battery.width - (leftFill.width) : ( (battery.width - leftFill.width) * _percent) / 100
        height: battery.height - (_topMargin * 2)
//        radius: 8
        color: _fillColor
//        visible: _percent > 8
    }

    Text {
        text: qsTr(_percent.toString()) + "%"
        anchors.top: battery.bottom
        anchors.horizontalCenter: battery.horizontalCenter
        anchors.topMargin: 2
        color: _fillColor
    }
}

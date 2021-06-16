import QtQuick 2.0

Rectangle {
    id: root
    width: 400
    height: 400
    color: "#19232D"

    property string _outlineColor: "white"
    property string _fillColor: "lime"

    Rectangle {
        id: battery
        anchors.centerIn: parent

        width: 200
        height: width * .4
        radius: width * .1
        color: root.color
        border.color: _outlineColor

    }

    Rectangle {
        id: terminal
        anchors.left: battery.right
        anchors.leftMargin: -1
        anchors.verticalCenter: battery.verticalCenter
        width: battery.width * .05
        height: battery.height * .4
        radius: width * .3
        color: _outlineColor
    }

    Rectangle {
        id: leftFill
        anchors.left: battery.left
        anchors.leftMargin: 2
        anchors.top: battery.top
        anchors.topMargin: 2

        width: battery.radius * 2
        height: battery.height - 4
        radius: battery.radius

        color: _fillColor
    }

    Rectangle {
        id: rightFill
        anchors.left: battery.left
        anchors.leftMargin: battery.width - width - 2
        anchors.top: battery.top
        anchors.topMargin: 2

        width: battery.radius * 2
        height: battery.height - 4
        radius: battery.radius
        color: _fillColor
    }

    Rectangle {
        id: mainFill
        anchors.left: battery.left
        anchors.leftMargin: leftFill.width/2
        anchors.top: battery.top
        anchors.topMargin: 2

        width: battery.width - leftFill.width
        height: battery.height - 4
        radius: 8
        color: _fillColor
    }
}

import QtQuick 2.0

Rectangle {
    property int faceValue: 0
    property int _width: 10
    property int _margin: 8

    width:         60
    height:        60
    color:         "#800000"
    border.color:  Qt.lighter(color)

    // center
    Rectangle {
        anchors.centerIn: parent
        width:            _width
        height:           _width
        radius:           _width * .5
        visible:          (faceValue % 2) != 0
    }

    // top-left
    Rectangle {
        anchors.left:     parent.left
        anchors.top:      parent.top
        anchors.margins:  _margin
        width:            _width
        height:           _width
        radius:           _width * .5
        visible:          faceValue > 1
    }

    // top-right
    Rectangle {
        anchors.right:    parent.right
        anchors.top:      parent.top
        anchors.margins:  _margin
        width:            _width
        height:           _width
        radius:           _width * .5
        visible:          faceValue > 3
    }

    // bottom-left
    Rectangle {
        anchors.left:     parent.left
        anchors.bottom:   parent.bottom
        anchors.margins:  _margin
        width:            _width
        height:           _width
        radius:           _width * .5
        visible:          faceValue > 3
    }

    // bottom-right
    Rectangle {
        anchors.right:    parent.right
        anchors.bottom:   parent.bottom
        anchors.margins:  _margin
        width:            _width
        height:           _width
        radius:           _width * .5
        visible:          faceValue > 1
    }

    // middle-left
    Rectangle {
        anchors.left:            parent.left
        anchors.verticalCenter:  parent.verticalCenter
        anchors.margins:         _margin
        width:                   _width
        height:                  _width
        radius:                  _width * .5
        visible:                 faceValue > 5
    }

    // middle-right
    Rectangle {
        anchors.right:           parent.right
        anchors.verticalCenter:  parent.verticalCenter
        anchors.margins:         _margin
        width:                   _width
        height:                  _width
        radius:                  _margin
        visible:                 faceValue > 5
    }
}

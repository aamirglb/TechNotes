import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Window   2.4

Window {

    id: root

    color:    "black"
    title:    "Curtain App"
    width:    (90 + 10) * 4
    height:   (90 + 10) * 4
//    width:    Screen.width * .4
//    height:   Screen.height * .4
    visible:  true

    Component {
        id: tileComponent

        Rectangle {
            property string  _title:       "Tile-"+(index+1)
            property int     _duration:    25
            property bool    _openCurtain: false
            property string _curtainColor: "steelblue"
            property string _tileColor:    "lime"

            id:               tile
            width:            80
            height:           width
            color:            _tileColor

            Label {
                text:            _title
                anchors.centerIn: parent
                color:            "black"
                font.bold:        true
                font.pixelSize:   12
            }

            Rectangle {
                id:            leftCurtain
                width:         tile.width / 2
                height:        tile.height
                color:         _curtainColor
                NumberAnimation on width {
                    id:            leftCurtainAnim
                    running:       false
                    from:          _openCurtain ? 0 : tile.width/2
                    to:            _openCurtain ? tile.width/2 : 0;
                    duration:      _duration
                }
            }

            Rectangle {
                id:            rightCurtain
                height:        tile.height
                width:         tile.width / 2
                x:             tile.width / 2
                color:         _curtainColor

                NumberAnimation on width {
                    id:        rightCurtainAnim
                    running:   false
                    from:      _openCurtain ? 0 : tile.width/2
                    to:        _openCurtain ? tile.width/2 : 0
                    duration:  _duration
                }
                NumberAnimation on x {
                    id:        xAnimation
                    running:   false
                    from:      _openCurtain ? tile.width : tile.width/2
                    to:        _openCurtain ? tile.width/2 : tile.width
                    duration:  _duration
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    leftCurtainAnim.running = true;
                    rightCurtainAnim.running = true;
                    xAnimation.running = true;
                    _openCurtain = !_openCurtain
                }
            }
        }
    }

    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 90; cellHeight: 90
        anchors.margins: 5


        model: 16
        delegate: tileComponent
//        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }
}

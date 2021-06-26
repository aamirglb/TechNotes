import QtQuick 2.0




Rectangle {
    id:            _root
    width:         800
    height:        600
    color:         "green"
    property int _score: 0
    property alias repeater: layout._repeater

    Row {
        property alias _repeater: rptr
        id:                layout
        spacing:           10
        anchors.top:       parent.top
        anchors.left:      parent.left
        anchors.margins:   10

        Repeater {
            id:             rptr
            model:          5
            Dice {
                faceValue:  0
            }
        }
    }

    Rectangle {
        anchors.left:            parent.left
        anchors.top:             layout.bottom
        Text {
            anchors.left:        parent.left
            anchors.top:         parent.top
            anchors.margins:     25
            anchors.topMargin:   25
            font.family:         "Helvetica"
            font.bold:           true
            font.pixelSize:      16
            color:               "white"
            text:                qsTr("Total Score: %1".arg(_score))
        }
    }

    Rectangle {
        width:             parent.width
        anchors.left:      parent.left
        anchors.bottom:    parent.bottom
        anchors.margins:   10
        height:            50
        color:             parent.color
        Text {
            anchors.centerIn:  parent
            font.bold:         true
            font.pixelSize:    20
            color:             "white"
            text:              qsTr("Press Spacebar To Roll The Dice.")
        }
    }

    focus:           true
    Keys.onSpacePressed: {
        let values = []
        let i = 0;
        while(i < 5) {
            let r = Math.floor((Math.random() * 10) % 7);
            if( r !== 0) {
                values.push(r);
                ++i;
            }
        }

        values = values.sort();
        let score = 0;
        for(let i = 0; i < 5; ++i) {
            score += values[i];
            repeater.itemAt(i).faceValue = values[i];
        }
        _score = score;
    }
}

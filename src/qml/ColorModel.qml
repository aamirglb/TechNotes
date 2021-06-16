import QtQuick 2.3

Item {
    Text {
        id:             _textMeasure
        text:           "X"
        color:          "white"
//        color:          "#19232D"
        font.family:    "opensans"
    }

    Component.onCompleted: {
        for (var i = 10; i < 360; i = i + 60) {
            var colorValue = Qt.hsla(i/360, 0.85, 0.5, 1);
            seriesColors.push(colorValue)
            colorListModel.append({"colorValue": colorValue.toString()})
        }
    }

    property var seriesColors: []

    ListModel {
        id: colorListModel
    }

    Column {
        width:              100
        spacing:            0
        anchors.centerIn:   parent

        Repeater {
            model: colorListModel
            delegate: Rectangle {
                width:      100
                height:     100 / 6
                color:      colorValue
                Text {
                    text:   colorValue
                    color:  "#202020"
                    font.pointSize:     _textMeasure.font.pointSize * 0.75
                    anchors.centerIn:   parent
                }
            }
        }
    }
}
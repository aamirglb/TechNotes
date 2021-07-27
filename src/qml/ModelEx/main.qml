import QtQuick 2.5

Rectangle {
    width: 440; height: 420

    Component {
        id: modelDelegate
        Rectangle {
            id: wrapper
            property bool showBold: ListView.isCurrentItem
            width: view.width
            height: 30
            //color: index % 2 ? 'lightgray' : 'white'
            color: ListView.isCurrentItem ? "lightsteelblue" : "white"
            
            Text {
                text: '%3. %1 - %2'.arg(model.country).arg(model.capital).arg(index+1)
                font.pointSize: 14
                anchors.verticalCenter: parent.verticalCenter
                //font.bold: ListView.isCurrentItem ? true : false
                font.bold: showBold
            }
        }
    }

    ListView {
        id: view        
        anchors.fill: parent
        model: cityModel
        delegate: modelDelegate

        highlight: Rectangle {
            color: "lightsteelblue"
            radius: 5
        }
        focus: true

        header: Rectangle {
            width: view.width
            height: 30
            color: "yellow"
            Text {
                text: "Country - Captial City"
                font.pointSize: 16
                font.bold: true
            }
        }
    }
}
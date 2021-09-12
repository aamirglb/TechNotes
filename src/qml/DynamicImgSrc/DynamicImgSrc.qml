import QtQuick 2.12

Item {
    id:     _root
    width:  (220 * 2) + 40
    height: (125 * 2) + 20

    property int  counter: 0
    property var  imageModel: ListModel {
        ListElement { name: "waiting.png" }
        ListElement { name: "waiting.png" }
        ListElement { name: "waiting.png" }
        ListElement { name: "waiting.png" }
    }

    Rectangle {
        anchors.fill:   parent
        color:          "#3c3c3c"
        focus:          true

        Grid {
            leftPadding: 10
            spacing: 10
            columns: 2

            Repeater {
                model: imageModel
                delegate: Image {
                    source: name
                }
            }
        }

        Keys.onPressed: {
            if (event.key === Qt.Key_Space) {
                let idx = counter % 4
                console.log("Spacekey pressed: counter: ", counter)
                if(counter < 4)
                    imageModel.insert(idx, {name: "1-2-24.376366-54.489468.png"})
                else
                    imageModel.insert(idx, {name: "waiting.png"})
                counter += 1
                if(counter >= 8) counter = 0
            }
        }
    }
}


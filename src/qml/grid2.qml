import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.5

Window {
    id: _root
    width: 400; height: 400
    visible:  true
    color: "#3c3c3c"
    property var testModel: [ ["A", "B", "C", "D"], ["E", "F", "G", "H", "I"], ["J", "K"], ["L", "M", "N", "O", "P"] ]
    property int count: 0
    ListView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true
        model: testModel.length
        delegate: numberDelegate
        spacing: 5
    }

    Component {
        id: numberDelegate

        Column {
            function getText(i, j) {
                let c = 0;
                if(i > 0) {
                    for(let k=0; k<i; ++k)
                        c += testModel[k].length;
                }

                return (c+j) + " - " + testModel[i][j];
            }
            property var idx: index
            property var txt: ""
            spacing: 5
            Repeater {
                model: testModel[index]
                Rectangle {
                    width: 50; height: 50
                    color: "lime"
                    Label {
                        anchors.centerIn: parent
                        text: getText(idx, index)
                        Component.onCompleted: {
                            count+=1;
                            console.log(count, testModel[idx][index])
                        }
                    }
                }
                Component.onCompleted: console.log(count)
            }
        }
    }

}

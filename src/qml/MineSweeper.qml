import QtQuick            2.0
import QtQuick.Layouts    1.12
import QtQuick.Dialogs    1.3

Rectangle {
    id: _root
    width:                    (80*10)+80
    height:                   (50*10)+60+(50 * 2)
    color:                    "white"

    property int _x:          -1
    property int _y:          -1
    property int _score:      0
    property bool firstClick: false
    property var mines:       []
    property alias _repeater: gridContainer.repeater

    function resetGame() {
        firstClick = false;
        _score = 0;
        mines = [];
        _x = -1;
        _y = -1;
        for(let i = 0; i < 100; ++i) {
            _repeater.itemAt(i)._clicked = false;
            _repeater.itemAt(i)._text = "";
            _repeater.itemAt(i).color = "lightgray";
        }
    }

    function getSurroundingCells(x, y) {
        var cells = []
        for (var i = -1; i < 2; ++i) {
            for (var j = -1; j < 2; ++j) {
                if(x+i >= 0 && x+i < 10 && y+j >=0 && y+j < 10) {
                    cells.push([x+i, y+j]);
                }
            }
        }
        return cells;
    }

    MessageDialog {
        id: gameOverDialog
        title: "Game Over!!"
        text: "BOOM!!. Game Over. Your Score is %1/70.".arg(_score)
        onAccepted: {
            resetGame();
        }
    }

    Rectangle {
        id: scoreLabel
        anchors.left: parent.left
        anchors.top: parent.top
        width: parent.width
        height: 45
        color: "#f0f0f0"
        border.color: Qt.lighter(color)

        Text {
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 24
            color: "green"
            text: qsTr("Score: %1/70".arg(_score));
        }
    }

    Rectangle {
        id: gridContainer
        anchors.left: parent.left
        anchors.top: scoreLabel.bottom

        width: parent.width
        height: parent.height - 100
        property alias repeater: grid._repeater
        GridLayout {
            id: grid
            anchors.fill: parent
            columns: 10
            Layout.rowSpan: 1
            Layout.columnSpan: 1
            property alias _repeater: repeater
            Repeater {
                id: repeater
                model: 100
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: _clicked ? "blue" : "lightgray"
                    border.color: "black"

                    property bool _clicked: false
                    property int _index: index
                    property string _color: "blue"
                    property string _text: ""

                    Text {
                        anchors.centerIn: parent
                        text: _text
                        font.pointSize: 15
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {

                            if(!_clicked) {
                                _clicked = true
                                var x = Math.floor(_index / 10)
                                var y = _index % 10

                                if(!_root.firstClick) {
                                    _root.firstClick = true;
                                    // polpulate the mines
                                    for(let i = 0; i < 100; ++i){
                                        mines.push(0);
                                    }

                                    let totalMines = 30;
                                    while(totalMines) {
                                        let rx = Math.floor(Math.random() * 100);
                                        if(rx === x*10+y)
                                            continue;
                                        mines[rx] = -1;
                                        --totalMines;
                                    }
                                }

                                if(mines[x*10+y] === -1) {
                                    console.log("BOOM!! Game Over.");
                                    gameOverDialog.visible = true;
                                    return;
                                }

                                if(_root._x !== -1 && _root._y !== -1) {
                                    // clear previous neighbours
                                    var c = getSurroundingCells(_root._x, _root._y);
                                    for(var j = 0; j < c.length; ++j) {
                                        const [_x, _y] = c[j]
                                        repeater.itemAt(_x*10+_y).color = "lightgray";
                                    }
                                }

                                // highlight neighbours
                                var cells = getSurroundingCells(x, y);
                                for(var i = 0; i < cells.length; ++i) {
                                    const [a, b] = cells[i]
                                    repeater.itemAt(a*10+b).color = "cyan";
                                }
                                repeater.itemAt(x*10+y).color = "blue";

                                // count neighbouring mines
                                let nMineCells = getSurroundingCells(x, y);
                                let mineCount = 0;
                                for(let i = 0; i < nMineCells.length; ++i) {
                                    const [a, b] = nMineCells[i];
                                    if(mines[a*10+b] === -1)
                                        mineCount++;
                                }

                                _score++;
                                _text = mineCount.toString();
                                _root._x = x;
                                _root._y = y;
                            }

                        }
                    }
                }
            }
        }
    }
    Rectangle {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 2
        anchors.bottomMargin: 2

        width: parent.width/2 - 4
        height: 45
        color: "lightgray"
        Text {
            anchors.centerIn: parent
            text: qsTr("All Mines")
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                for(let i = 0; i < 100; ++i) {
                    if(mines[i] === -1)
                        _repeater.itemAt(i).color = "red";
                }
            }
            onReleased: {
                for(let i = 0; i < 100; ++i) {
                    if(mines[i] === -1)
                        _repeater.itemAt(i).color = "lightgray";
                }
                // color neighbouring cell cyan
                let cells = getSurroundingCells(_x, _y);
                for(let j = 0; j < cells.length; ++j) {
                    let [x, y] = cells[j];
                    if(!(_x === x && _y === y)) {
                        _repeater.itemAt(x*10+y).color = "cyan";
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 2
        anchors.bottomMargin: 2

        width: parent.width/2 - 4
        height: 45
        color: "lightgray"
        Text {
            anchors.centerIn: parent
            text: qsTr("Surrounding Mines")
        }
        MouseArea {
            anchors.fill: parent
            onPressed: {
                let cells = getSurroundingCells(_root._x, _root._y);
                for(let i = 0; i < cells.length; ++i) {
                    let [x, y] = cells[i];
                    if(mines[x*10+y] === -1)
                        _repeater.itemAt(x*10+y).color = "red";
                }
                            }
            onReleased: {
                let cells = getSurroundingCells(_root._x, _root._y);
                for(let i = 0; i < cells.length; ++i) {
                    const [x, y] = cells[i];
                    if(mines[x*10+y] === -1)
                        _repeater.itemAt(x*10+y).color = "cyan";
                }
            }
        }
    }
}

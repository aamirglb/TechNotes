import QtQuick 2.0
import QtQuick.Layouts 1.12
Rectangle {
    id: _root
    width: (80*10)+80
    height: (50*10)+60
//    color: "#ECE9D6"
    color: "white"
    property int _x: -1
    property int _y: -1
    property bool firstClick: false
    property var mines: []

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

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 10
        Layout.rowSpan: 1
        Layout.columnSpan: 1
        Repeater {
            id: repeater
            model: 100
            Rectangle {
                width: 80
                height: 50
                color: _clicked ? "blue" : "lightgray"
                border.color: "black"

                property bool _clicked: false
                property int _index: index
                property string _color: "blue"
                property string _text: ""

                Text {
                    anchors.centerIn: parent
                    text: _text
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(!_root.firstClick) {
                            _root.firstClick = true;
                            // polpulate the mines
                            for(let i = 0; i < 100; ++i){
                                mines.push(0);
                            }

                            let totalMines = 30;
                            while(totalMines) {
                                let rx = Math.floor(Math.random() * 100);
                                console.log(rx);
                                mines[rx] = -1;
                                --totalMines;
                            }
                        }

                        if(!_clicked) {
                            if(_root._x !== -1 && _root._y !== -1) {
                                // clear previous neighbours
                                var c = getSurroundingCells(_root._x, _root._y);
                                for(var j = 0; j < c.length; ++j) {
                                    const [_x, _y] = c[j]
                                    repeater.itemAt(_x*10+_y).color = "lightgray";
                                }
                            }
                            _clicked = true
                            var x = Math.floor(_index / 10)
                            var y = _index % 10

                            if(mines[x*10+y] == -1) {
                                console.log("BOOM!! Game Over.");
                                Qt.quit();
                            }

                            console.log(_index, "(", x, ",", y, ")", " clicked.")
                            _text = "1"

                            // highlight neighbours
                            var cells = getSurroundingCells(x, y);
                            for(var i = 0; i < cells.length; ++i) {
                                const [a, b] = cells[i]
                                repeater.itemAt(a*10+b).color = "cyan";
                            }
                            _root._x = x;
                            _root._y = y;
                        }

                    }
                }
            }
        }
    }
}

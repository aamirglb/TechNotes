import QtQuick 2.12

Item {
    width: 200; height: 200
    Text {
        width: 180; height: 120
        text: qsTr("A very long text field")
        elide: Text.ElideMiddle
        style: Text.Sunken
        styleColor: "#FF4444"
        verticalAlignment: Text.AlignHCenter | Text.AlignVCenter
        font.pointSize: 16
    }
}

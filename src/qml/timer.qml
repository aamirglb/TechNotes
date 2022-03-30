import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Window   2.4

Window {

    function msToHMS( ms ) {
        let seconds = ms / 1000;
        let hours = parseInt( seconds / 3600 );
        seconds = seconds % 3600;
        let minutes = parseInt( seconds / 60 );
        seconds = parseInt(seconds % 60);
        ms = ms % 1000;

        if(hours < 10) hours = "0" + hours.toString();
        if(minutes < 10) minutes = '0' + minutes;
        if(seconds < 10) seconds = '0' + seconds;
        if(ms < 10) {
            ms = '00' + ms;
        } else if(ms < 100) {
            ms = '0' + ms;
        }
        return "%1:%2:%3.%4".arg(hours).arg(minutes).arg(seconds).arg(ms);
    }

    id: root
    property var _counter: 0
    property var _interval: 50
    //    color: "transparent"
    color: "black"
    title: "Timer App"
    width: 1920 * 0.8
    height: 1080 * 0.8
    visible: true

    Label {
        id: label
        text: "00:00:00.000"
        color: "lime"
        font.pixelSize: 48*5
        font.bold: true
        anchors.centerIn: parent
    }

    Timer {
        interval: _interval; running: true; repeat: true
        onTriggered: {
            ++_counter;
            label.text = msToHMS(_counter * _interval);
        }
    }
}

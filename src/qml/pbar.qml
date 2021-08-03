import QtQuick 2.0
import QtQuick.Controls 1.5

Rectangle {
    width: 400; height: 400

    ProgressBar {
        id: progressBar
        anchors.centerIn: parent
        value: 0.0
        Behavior on value {
            NumberAnimation {
                duration: 750
            }
        }
    }

    Timer {
        interval: 1000
        running: true; repeat: true
        onTriggered: progressBar.value += 0.1
    }
}

import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Window   2.12

Item {
    Button {
        id: ldbutton
        onClicked: winld.active = true
        Rectangle {
            id: ldindic
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
            }
            width: height
            color: winld.active ? 'green' : 'red'
        }

        Loader {
            id: winld
            active: false
            sourceComponent: Window {
                width: 100
                height: 100
                color: 'green'
                visible: true
                onClosing: winld.active = false
            }
        }
    }
}

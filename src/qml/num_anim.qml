import QtQuick 2.12
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 400
    height: 640
    property int toHeight: 400

    Rectangle{
        id: rect
        anchors.centerIn: parent
        height: 100
        width: 100
        color: "blue"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                na.running = true
                if(toHeight == 400) {
                    toHeight = 100;
                } else {
                    toHeight = 400;
                }
                na.restart();
            }

        }
        NumberAnimation {
            id: na //ID of the QML Animation type
            target: rect //The target item on which the animation should run
            property: "height"
            duration: 3000 //The duration for which the animation should run
            from: rect.height //The initial numeric value of the property declared in 'property'
            to: toHeight //The final numeric value of the property declared in 'property'
        }
    }
}

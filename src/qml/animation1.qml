import QtQuick 2.0

import QtQuick 2.0

Rectangle {
    id: root
    width: 400; height: 400
    property bool zoom: false
    property int animDuration: 2000

    Rectangle {
        id: rect
        width: 100; height: 100
        color: "red"
        onWidthChanged: { if(width==5) {
                anim.running = false;
                zoom = false;
                anim.running = true;
            } else if(width == 100) {
                anim.running = false;
                zoom = true;
                anim.running = true;
            }
        }
        Rectangle {
            width: 10; height: 10; radius: 5
            color: "red"
            x: 10; y: 10
        }

        ParallelAnimation {
            id: anim
            running: true
            NumberAnimation {
                target: rect;
                property: "x";
                from: root.zomm ? 100 : 50
                to: root.zoom ? 50 : 100;
                duration: animDuration
            }

            NumberAnimation {
                target: rect;
                property: "y";
                from: root.zoom ? 100 : 50
                to: root.zoom ? 50 : 100;
                duration: animDuration
            }

            NumberAnimation {
                target: rect;
                property: "width";
                from: root.zoom ? 100 : 5
                to: root.zoom ? 5 : 100;
                duration: animDuration
            }

            NumberAnimation {
                target: rect;
                property: "height";
                from: root.zoom ? 100 : 5
                to: root.zoom ? 5 : 100;
                duration: animDuration
            }
        }
    }
}


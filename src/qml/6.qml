// EasingCurves.qml

import QtQuick 2.5
import QtQuick.Layouts 1.2

Rectangle {
    id: root
    width: 800
    height: 600
    property int duration: 8*1000
    property alias w: ball.width
    property alias h: ball.height
    property var colors: ['red', 'white', 'black', 'yellow']
    property int idx: 0

    ListModel {
        id: posModel
    }

    Repeater {
        model: posModel
        anchors.fill: parent
        z: 90
        delegate: Rectangle {
            width: 10; height: 10; radius: 5;
            color: colors[idx]
            x: xPos+(w/2); y: yPos+(h/2); z: 91
//            Component.onCompleted: {
//                console.log("creating rect at: ", xPos, yPos)
//            }
        }
    }

    Rectangle {
            id: sky
            width: parent.width
            height: 200
            z: 1
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#0080FF" }
                GradientStop { position: 1.0; color: "#66CCFF" }
            }
        }
        Rectangle {
            id: ground
            anchors.top: sky.bottom
            anchors.bottom: root.bottom
            width: parent.width
            z: 1
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#00FF00" }
                GradientStop { position: 1.0; color: "#00803F" }
            }
        }

        Image {
            id: ball
            property int cnt: 0
            x: 0; y: root.height-height; z: 95
            source: "ball.png"

            onXChanged: {
                cnt += 1;
                if(cnt % 5 == 0) {
                    posModel.append({"xPos": Math.floor(ball.x), "yPos": Math.floor(ball.y)})
//                    console.log(ball.x, ball.y)
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ball.x = 0;
                    ball.y = root.height-ball.height;
                    ball.rotation = 0;
                    idx = Math.random() * 4
                    posModel.clear()
                    anim.restart()
                }
            }
        }

        ParallelAnimation {
                id: anim
                SequentialAnimation {
                    NumberAnimation {
                        target: ball
                        properties: "y"
                        to: 20
                        duration: root.duration * 0.4
                        easing.type: Easing.OutCirc
                    }
                    NumberAnimation {
                        target: ball
                        properties: "y"
                        to: root.height-ball.height
                        duration: root.duration * 0.6
                        easing.type: Easing.OutBounce
                    }
                }
                NumberAnimation {
                    target: ball
                    properties: "x"
                    to: root.width-ball.width
                    duration: root.duration
                }
                RotationAnimation {
                    target: ball
                    properties: "rotation"
                    to: 720
                    duration: root.duration
                }
               Component.onCompleted: {
                   console.log(ball.x);
                   console.log(root.width - ball.width)
               }
            }
}

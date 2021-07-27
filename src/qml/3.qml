import QtQuick 2.12

Item {
    width: 200; height: 120 * 3
    Rectangle {
        id: rect1
        x: 12; y: 12
        width: 176; height: 96
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "slategray" }
        }
        border.color: "slategray"
    }

    Rectangle {
        id: rect2
        x: 12; y: (12 * 2) + (96 * 1)
        width: 176; height: 96
        gradient: Gradient {
            GradientStop { position: 0.0; color: "red" }
            GradientStop { position: 0.5; color: "green" }
            GradientStop { position: 1.0; color: "blue" }
        }
        border.color: "black"
    }

    Rectangle {
        id: rect3
        x: 12; y: (12 * 3) + (96 * 2)
        width: 176; height: 96
        gradient: Gradient {
            GradientStop { position: 0.0; color: "black" }
            GradientStop { position: 1.0; color: "white" }
        }
        border.color: "black"
    }
}

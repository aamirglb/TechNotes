import QtQuick 2.12

Rectangle {
    id: root
    width: 220; height: 240
    color: "#4A4A4A"

    Text {
        id: label
        anchors.centerIn: parent
        property int spacePresses: 0
        text: "Space pressed: " + spacePresses + " times."
        color: "white"
        onTextChanged: console.log("text change to: ", text)
        focus: true
        Keys.onSpacePressed: {
            increment();
        }

        Keys.onEscapePressed: {
            reset()
        }

        function increment() {
            spacePresses += 1;
        }

        function reset() {
            spacePresses = 0;
        }
    }
}

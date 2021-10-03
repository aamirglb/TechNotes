import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    ColumnLayout {
        anchors.fill: parent
        Button {
            Layout.fillWidth: true
            text: "PushButton"
        }
        Button {
            Layout.fillWidth: true
            text: "PushButton"
        }
        Label {
            Layout.fillWidth: true
            text: "TextLabel"
        }
        Item {
            // spacer item
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle { anchors.fill: parent; color: "#ffaaaa" } // to visualize the spacer
        }
    }
}

import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.6


Rectangle {
    id: root
    width: 800; height: 800
    color: "#19232D"
    property var rosStatus: [0x1AA, 0x055, 0x1FF, 0x0]

    function getStatus(value, mask) {
        if( (value & mask) === mask)
            return "Running";
        else
            return "Stopped";
    }

    Column {
        anchors.fill: parent
        Rectangle {
            id: heading
            width: parent.width
            height: parent.height * 0.05
            color: "#19232D"
            Label {
                anchors.centerIn: parent
                text: "ROS Status"
                font.bold: true
                font.pixelSize: 18
                color: "white"
            }
        }
        ScrollView {
            contentWidth: root.width
            contentHeight: root.height - heading.height
//            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
//            width: root.width
//            height: root.height - heading.height
            clip: true
            ListView {
//                anchors.fill: parent
                model: 5
                delegate: rosStatusDelegate
            }
        }
    }

    Component {
        id: rosStatusDelegate
        Column {
            property int vIdx: index
            Label {
                text: "/uav_" + (index+1)
                font.pixelSize: 18
                color: "white"
            }

            GridLayout {
                columns: 2
                Repeater {
                    model: [
                        "surveillance_watchdog_node", getStatus(rosStatus[vIdx], 0x1),
                        "surveillance_ai_node", getStatus(rosStatus[vIdx], 0x2),
                        "image_server_node", getStatus(rosStatus[vIdx], 0x4),
                        "nx_temp_status_node",  getStatus(rosStatus[vIdx], 0x8),
                        "camera_manager_node", getStatus(rosStatus[vIdx], 0x10),
                        "darknet_ros", getStatus(rosStatus[vIdx], 0x20),
                        "mavros",  getStatus(rosStatus[vIdx], 0x40),
                        "rgb_camera_node",  getStatus(rosStatus[vIdx], 0x80),
                        "mavlink_bridge", getStatus(rosStatus[vIdx], 0x100),
                    ]
                    delegate:
                        Label {
                        property string t: (((index+1) % 2) !== 0) ? "\t"+modelData+":\t" : modelData
                        property string c: (((index+1) % 2) !== 0) ? "white" : ((modelData === "Running") ? "lime" : "red")
                            text: t
                            font.pointSize:         12
                            color: c
                        }
                    }
                }
            }
        }
}

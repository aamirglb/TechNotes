import QtQuick 2.12

Rectangle {
    id: relay

    signal messageReceived(string preson, string notice)

    Component.onCompleted: {
        relay.messageReceived.connect(sendToPost)
        relay.messageReceived.connect(sendToTelegraph)
        relay.messageReceived.connect(sendToEmail)
        relay.messageReceived("Tom", "Happy New Year!!")
    }

    function sendToPost(person, notice) {
        console.log("Sending to post: " + person + ", " + notice)
    }

    function sendToTelegraph(person, notice) {
        console.log("Sending to telegraph: " + person + ", " + notice)
    }

    function sendToEmail(person, notice) {
        console.log("Sending to email: " + person + ", " + notice)
    }
}
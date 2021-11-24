import QtQuick 2.12

Item {
    id: window
    width: 100; height: 100

    Rectangle {
        id: mainRect
        width: 30; height: 30
        border.color: "black"
    }

    Item { id: myContainer }

    Component {
        id: myComponent
        Rectangle {
            property alias xPos: rect.x
            property alias color: rect.color

            id: rect
            width: 50; height: 50
            x: 30
            color: "red"
            onWidthChanged: console.log("[Rectangle onWidthChanged()]", "width", width)
        }
    }

    function loadItems() {
        let colors = ["red", "blue"]
        for(let i = 0; i < 2; ++i) {
        var item = myComponent.createObject(myContainer); //, {"xPos": i*30, "color": colors[i]})
            item.xPos = (i+1)*30;
            item.color = colors[i];
        if (item === null) {
            console.log("[loadItems()]", "ERROR", "Component::createObject()")
        }
        }
    }

    Component.onCompleted: {
        loadItems()
        mainRect.width = 31
        mainRect.width = 32
        mainRect.width = 33
    }
}

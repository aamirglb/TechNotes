var arrayLines=[]
var lineComplete=false

function createElements(point) {

    var componentMarker = Qt.createComponent("Marker.qml");

    if (componentMarker.status === Component.Ready) {
        var markerFirstCorner = componentMarker.createObject(themap);
        markerFirstCorner.coordinate = themap.toCoordinate(point)

        themap.addMapItem(markerFirstCorner)
    }else{
        console.log("Marker not created")
    }

    var theLine

    if(changeMode===0){

        //Polyline mode
        if(arrayLines.length===0){
            createLine(point)
        }else{
            theLine = arrayLines[arrayLines.length-1]

            theLine.mainPolyline.addCoordinate(themap.toCoordinate(point))
        }

    }else{
        //Array of lines

        if(arrayLines.length===0 || !lineComplete){
            createLine(point)
            lineComplete=true
        }else{
            theLine = arrayLines[arrayLines.length-1]

            theLine.mainPolyline.addCoordinate(themap.toCoordinate(point))

            lineComplete=false
        }
    }
}

function createLine(point){

    var componentLine = Qt.createComponent("Line.qml")

    if (componentLine.status === Component.Ready) {
        var lineFirstCorner = componentLine.createObject(themap);
        lineFirstCorner.mainPolyline.addCoordinate(themap.toCoordinate(point))

        themap.addMapItem(lineFirstCorner)
        arrayLines.push(lineFirstCorner)
    }else{
        console.log("Line not created")
    }
}

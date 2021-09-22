import QtQuick          2.12                                                                                                                                                  
import QtQuick.Window   2.12
import QtLocation       5.6
import QtPositioning    5.6
import QtQuick.Controls 2.5

MapPolyline {

    property alias mainPolyline: mainPolyline

    id: mainPolyline
    line.width: 3
    line.color: 'blue'
}

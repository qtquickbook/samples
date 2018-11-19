import QtQuick 2.9
import QtQuick.Window 2.2
import Color 1.0

Window {
    visible: true
    width: 300
    height: 300

    Color{
        id: color
    }

    Rectangle {
        id: colorRect
        anchors.fill: parent
        color: color.rgb
    }
}

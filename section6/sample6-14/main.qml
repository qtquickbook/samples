import QtQuick 2.9
import QtQuick.Window 2.2
import Circle 1.0

Window {
    visible: true
    width: 200
    height: 200

    Circle  {
        id: circle
        anchors.fill: parent
    }
}

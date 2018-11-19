import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 300
    height: 100
    Item {
        anchors.fill: parent
        Rectangle {
            id: redRect
            width: 100
            height: 100
            color: "red"
        }
        Rectangle {
            id: greenRect
            anchors.left: redRect.right
            width: 100
            height: 100
            color: "green"
        }
        Rectangle {
            id: blueRect
            anchors.left: greenRect.right
            width: 100
            height: 100
            color: "blue"
        }
    }
}

import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100
    Rectangle {
       id: red
        color: "red"
        width: 100
        height: 100
    }
    Rectangle {
        id: blue
        color: "blue"
        width: red.width
        height: red.height
        x: red.x + red.width

        Rectangle {
          id: green
            color: "green"
            anchors.fill: parent
        }
    }
}

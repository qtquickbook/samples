import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 300
    height: 100
    Row {
        Repeater {
            model: 3
            Rectangle {
                width: 100
                height: 100
                border.width: 1
                color: "red"
            }
        }
    }
}

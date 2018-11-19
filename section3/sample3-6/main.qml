import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100
    Rectangle {
        color: "red"
        width: 100
        height: 100
    }
    Rectangle {
        color: "blue"
        width: 100
        height: 100
        x: 100
    }
}

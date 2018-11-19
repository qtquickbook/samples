import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 100
    height: 100
    property int mySize: 50

    Rectangle {
        id: red
        color: "red"
        width: mySize
        height: mySize
    }
}

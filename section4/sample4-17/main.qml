import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100

    Text {
        id: label
        anchors.fill: parent
        text: ""
    }
    MouseArea {
        acceptedButtons: Qt.AllButtons
        anchors.fill: parent
        onPressed: {
            if (pressedButtons & Qt.LeftButton) {
                label.text = "Left"
            } else if (pressedButtons & Qt.RightButton) {
                label.text = "Right"
            } else {
                label.text = "Middle"
            }
        }
    }
}

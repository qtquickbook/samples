import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100

    Text {
        id: keyPressedText
        anchors.fill: parent
    }

    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Left) {
                keyPressedText.text = "Left Key was pressed."
            } else {
                keyPressedText.text = "Left Key was not pressed."
            }
        }
    }
}

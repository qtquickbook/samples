import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 100
    height: 100

    Rectangle {
        id: rect
        anchors.fill: parent

        Text {
            id: myText
            anchors.fill: parent
            text: "Not Pressed"
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                rect.color = Qt.rgba(Math.random(),
                                     Math.random(),
                                     Math.random(),
                                     1);
            }
            onPressedChanged: {
                if (pressed) {
                    myText.text = "Pressed"
                } else {
                    myText.text = "Not Pressed"
                }
            }
        }
    }
}

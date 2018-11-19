import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 100
    height: 100
    header: Rectangle {
        width: parent.width
        height: 30
        color: "red"
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            text: "header"
        }
    }
    footer: Rectangle {
        width: parent.width
        height: 30
        color: "blue"
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            text: "footer"
        }
    }
}

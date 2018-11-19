import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 100
    height: 100
    signal stringAdd(string str)

    Component.onCompleted: {
        stringAdd.connect(stringAdded)
    }

    Text {
        id: text
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: stringAdd("a")
    }

    function stringAdded(str) {
        text.text += str
    }
}

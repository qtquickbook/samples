import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100
    Text {
        id: text1
        text: "abcdefghijklmnopqrstuvwxyz"
    }
    TextInput {
        anchors.top: text1.bottom
        width: 200
        onEditingFinished: text1.text = text
        text: "abcde"
    }
}

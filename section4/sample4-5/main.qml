import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 50

    Text {
        id: text1
        width: 50
        height: 50
        text: "abcdefghijklmnopqrstuvwxyz"
        clip: true
    }
}

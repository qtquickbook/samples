import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100

    Column {
        Text {
            id: text1
            focus: true
            width: 200
            height: 50
            text: "focus: " + focus + " activeFocus: " + activeFocus
        }
        Text {
            id: text2
            focus: true
            width: 200
            height: 50
            text: "focus: " + focus + " activeFocus: " + activeFocus
        }
    }
}

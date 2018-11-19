import QtQuick 2.9
import QtQuick.Controls 2.2

Row {
    Button {
        id: button
        text: "click"
        onClicked: {
            valueText.text = Math.random()
        }
    }
    Text {
        id: valueText
        text: "0"
    }
}

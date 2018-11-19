import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 200

    Rectangle {
        id: rect
        anchors.fill: parent
        state: "RED"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                switch (rect.state) {
                case "RED":
                    rect.state = "BLACK"
                    break
                case "BLACK":
                    rect.state = "RED"
                    break
                }
            }
        }

        states: [
            State {
                name: "RED"
                PropertyChanges {
                    target: rect
                    color: "red"
                }
            },
            State {
                name: "BLACK"
                PropertyChanges {
                    target: rect
                    color: "black"
                }
            }
        ]

        transitions: [
            Transition {
                from: "RED"
                to: "BLACK"
                ColorAnimation {
                    duration: 1000
                }
            },
            Transition {
                from: "BLACK"
                to: "RED"
                ColorAnimation {
                    duration: 1000
                }
            }
        ]
    }
}

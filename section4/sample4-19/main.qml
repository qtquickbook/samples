import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: pageLoader.source = "CustomItem.qml"
    }

    Loader {
        id: pageLoader
    }
}

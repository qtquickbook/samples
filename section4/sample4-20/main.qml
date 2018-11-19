import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: {
            pageLoader.sourceComponent = customComponent
        }
    }

    Loader {
        id: pageLoader
    }

    Component {
        id: customComponent
        CustomItem {
            id: customItem
        }
    }
}

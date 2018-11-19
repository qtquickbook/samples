import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

Window {
    visible: true
    width: 200
    height: 100

    Column {
        FocusScope {
            id: scope1
            width: 200
            height: 50
            focus: true
            TextField {
                id: text1
                focus: true
                anchors.fill: parent
            }
            KeyNavigation.tab: scope2
        }
        FocusScope {
            id: scope2
            width: 200
            height: 50
            TextField {
                id: text2
                anchors.fill: parent
            }
            KeyNavigation.tab: scope1
        }
    }
}

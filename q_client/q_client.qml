import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0

ApplicationWindow {
    id: applicationwindow1
    title: qsTr("MCL Queue Client")
    width: 640
    height: 480
    
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Label {
        id: label1
        x: 8
        y: 8
        width: 448
        height: 39
        text: "Queue Client"
    }

    ListView {
        id: list_view1
        x: 8
        y: 97
        width: 624
        height: 375
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 97
        anchors.fill: parent
        delegate: Item {
            x: 5
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
    }

    Button {
        id: button1
        x: 8
        y: 60
        text: "Button"
    }
}

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    title: qsTr("Hello World")
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
        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Copy Log")
            }
            MenuItem {
                text: qsTr("Preferences")
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("Queue Client Help")
            }
            MenuItem {
                text: qsTr("About Queue Client")
            }
        }
    }

    ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 2
            ToolButton { iconSource: "images/online.png" }
            ToolButton { iconSource: "images/offline.png" }
            Label { text: "Search Log:" }
            TextField { Layout.fillWidth: true; placeholderText: "Search"; }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 2
        Label { text: "Local Server Log" }
        TextArea { Layout.fillWidth: true }
        Label { text: "Remote Log" }
        TableView {
            Layout.fillWidth: true;
        }
    }


}

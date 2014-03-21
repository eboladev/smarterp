import QtQuick 1.1

Rectangle {
    id: rectangle1
    width: 360
    height: 360
    Text {
        x: 55
        width: 250
        height: 21
        text: qsTr("Paper Consumption Data Entry")
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.pointSize: 12
        anchors.horizontalCenterOffset: 0
    }
    MouseArea {
        x: 0
        y: 0
        width: 360
        height: 360
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}

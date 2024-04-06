import QtQuick
import QtQuick.Controls.Fusion

Window {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Open Sesame")

    RoundButton{
        id: connectToHostBtn
        anchors.centerIn: parent
        text: "Unlock"
        height: parent.height /6
        width: parent.width /4
    }
}

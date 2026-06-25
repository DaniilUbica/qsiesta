import QtQuick
import QtQuick.Controls

Item {
    id: root

    property url url

    Text {
        anchors.centerIn: parent
        text: qsTr("Web view is not supported on this platform")
        color: palette.windowText
        font.pixelSize: 16
    }

    SystemPalette { id: palette }
}

import QtQuick

Loader {
    source: gameManager ? gameManager.qmlSource : ""
    anchors.fill: parent
    onLoaded: item.forceActiveFocus()
}

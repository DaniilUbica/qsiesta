import QtQuick

Item {
    id: root
    width: snakeManager.cellSize() * snakeManager.fieldSize()
    height: snakeManager.cellSize() * snakeManager.fieldSize()

    Rectangle {
        id: field
        anchors.fill: parent
        color: "blue"
        opacity: 0.6
    }
}

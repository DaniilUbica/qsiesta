import QtQuick

import "."

FocusScope {
    id: root
    focus: true

    Component.onCompleted: {
        root.forceActiveFocus()
    }

    Keys.onPressed: (event) => {
        snakeManager.onKeyPressed(event.key)
    }

    QMGameField {
        id: field
        x: (root.width  - snakeManager.fieldSize() * snakeManager.cellSize()) / 2
        y: (root.height - snakeManager.fieldSize() * snakeManager.cellSize()) / 2
    }

    Rectangle {
        id: food
        width: snakeManager.cellSize()
        height: snakeManager.cellSize()
        x: field.x + snakeManager.foodCell.x * snakeManager.cellSize()
        y: field.y + snakeManager.foodCell.y * snakeManager.cellSize()
        color: "red"
    }

    Repeater {
        id: snake
        model: snakeManager.snakeBody

        Rectangle {
            width: snakeManager.cellSize()
            height: snakeManager.cellSize()
            x: field.x + modelData.x * snakeManager.cellSize()
            y: field.y + modelData.y * snakeManager.cellSize()
            color: "green"
        }
    }
}

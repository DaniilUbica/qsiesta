import QtQuick
import QtQuick.Controls

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

    SystemPalette {
        id: palette
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: palette.window
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

    QMGameOverlay {
        id: gameOverlay
        anchors.fill: parent
        showStartScreen: !snakeManager.gameRunning && !gameOverlay.showLoseScreen
        currentScore: snakeManager.snakeBody.length - 1

        onStartButtonClicked: {
            snakeManager.startGame()
        }

        onRestartButtonClicked: {
            snakeManager.toInitialState()
            snakeManager.startGame()
        }
    }

    Connections {
        target: snakeManager

        function onGameOver() {
            gameOverlay.showLoseScreen = true
        }
    }
}

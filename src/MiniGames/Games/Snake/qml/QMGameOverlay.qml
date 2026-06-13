import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    property bool showStartScreen: false
    property bool showLoseScreen: false

    property int currentScore: 0

    signal startButtonClicked()
    signal restartButtonClicked()

    SystemPalette {
        id: palette
    }

    Loader {
        id: content
        anchors.fill: parent
        sourceComponent: showLoseScreen ? loseScreenComp : showStartScreen ? startScreenComp : gameScreenComp
    }

    Component {
        id: startScreenComp

        Item {
            anchors.fill: parent

            Rectangle {
                id: dimmer
                anchors.fill: parent
                color: "black"
                opacity: 0.3
            }

            ColumnLayout {
                anchors.centerIn: parent

                Text {
                    id: gameName
                    font.bold: true
                    color: palette.windowText
                    font.pixelSize: 32
                    text: qsTr("Snake game")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    id: gameDescription
                    color: palette.windowText
                    font.pixelSize: 20
                    text: qsTr("A classic snake game")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }

                Button {
                    id: startButton
                    text: qsTr("Start")
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignHCenter

                    onClicked: {
                        root.showStartScreen = false
                        root.startButtonClicked()
                    }
                }
            }
        }
    }

    Component {
        id: gameScreenComp

        Item {
            anchors.fill: parent

            Text {
                id: scoreText
                font.bold: true
                color: palette.windowText
                font.pixelSize: 32
                text: root.currentScore
                horizontalAlignment: Text.AlignHCenter
                anchors.top: parent.top
                anchors.topMargin: 16
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component {
        id: loseScreenComp

        Item {
            anchors.fill: parent

            Rectangle {
                id: dimmer
                anchors.fill: parent
                color: "black"
                opacity: 0.3
            }

            ColumnLayout {
                anchors.centerIn: parent

                Text {
                    id: loseText
                    font.bold: true
                    color: palette.windowText
                    font.pixelSize: 32
                    text: qsTr("Game over")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }

                Text {
                    id: scoreText
                    color: palette.windowText
                    font.pixelSize: 20
                    text: qsTr("Your score: ") + root.currentScore
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }


                Button {
                    id: restartButton
                    text: qsTr("Restart")
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignHCenter

                    onClicked: {
                        root.showLoseScreen = false
                        root.restartButtonClicked()
                    }
                }
            }
        }
    }
}

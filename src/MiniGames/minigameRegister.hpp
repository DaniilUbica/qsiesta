#pragma once

#include "MiniGamesManager/miniGamesManager.h"
#include "minigamesDefines.h"

#include "Games/Snake/GameManager/gameManager.h"

#include <QQmlContext>

static void initGamesResources() {
    Q_INIT_RESOURCE(Snake);
}

namespace QSiesta::Internal {
namespace minigame {

namespace {

    static defines::MiniGameEntry snakeGame(QQmlContext* ctxt, MiniGamesManager* parent) {
        const auto snake = new minigame::snake::GameManager(parent);
        ctxt->setContextProperty("snakeManager", snake);

        return { QUrl("qrc:/snake/QMSnakeGame.qml"), snake };
    }

}

static std::map<MiniGame, defines::MiniGameEntry> initMiniGames(QQmlContext* ctxt, MiniGamesManager* parent) {
    if (!ctxt) {
        assert(false);
        return {};
    }

    initGamesResources();

    return {
        { MiniGame::Snake, snakeGame(ctxt, parent) }
    };
}

} // namespace minigame
} // namespace QSiesta::Internal
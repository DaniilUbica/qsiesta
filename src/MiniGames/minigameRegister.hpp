#pragma once

#include "MiniGamesManager/miniGamesManager.h"

#include "Games/Snake/GameManager/gameManager.h"

#include <QQmlContext>

namespace QSiesta::Internal {
namespace minigame {

static void registerMiniGames(MiniGamesManager* manager) {
    if (!manager) {
        assert(false);
        return;
    }

    manager->registerGame(new snake::GameManager(manager));
}

} // namespace minigame
} // namespace QSiesta::Internal
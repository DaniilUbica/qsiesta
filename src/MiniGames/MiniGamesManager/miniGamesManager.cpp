#include "miniGamesManager.h"

#include "minigameRegister.hpp"

#include <QQuickView>
#include <QQmlContext>

using namespace QSiesta::Internal;
using namespace minigame;

MiniGamesManager::MiniGamesManager(QObject* parent) : QObject(parent) {}

void MiniGamesManager::setupContext(QQuickView* view) {
    registerMiniGames(this);

    auto* ctx = view->rootContext();
    for (auto* game : m_games) {
        game->setupGameContext(ctx);
    }

    ctx->setContextProperty("gameManager", this);
}

void MiniGamesManager::setCurrentGame(base::GameManagerBase* game) {
    m_currentSource = game->gameDescription().qmlSource;
    Q_EMIT currentGameChanged();
}

void MiniGamesManager::registerGame(base::GameManagerBase* game) {
    m_games.push_back(game);
}

const std::list<base::GameManagerBase*>& MiniGamesManager::games() const {
    return m_games;
}
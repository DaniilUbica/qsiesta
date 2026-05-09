#include "miniGamesManager.h"

#include "minigameRegister.hpp"

#include <QQuickView>
#include <QQmlContext>

using namespace QSiesta::Internal;
using namespace minigame;

MiniGamesManager::MiniGamesManager(QObject* parent) : QObject(parent) {}

void MiniGamesManager::setupContext(QQuickView* view) {
    m_games = initMiniGames(view->rootContext(), this);

    view->rootContext()->setContextProperty("gameManager", this);
}

void MiniGamesManager::setCurrentGame(MiniGame game) {
    if (!m_games.contains(game)) {
        return;
    }

    m_currentSource = m_games[game].qmlSource;
    Q_EMIT currentGameChanged();
}

void MiniGamesManager::registerGame(MiniGame game, const QUrl& qmlSource, QObject* manager) {
    m_games[game] = { qmlSource, manager };
}

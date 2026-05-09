#include "gameManagerBase.h"

using namespace QSiesta::Internal::minigame::base;

GameManagerBase::GameManagerBase(int tickIntervalMs, QObject* parent) : QObject(parent) {
    m_timer = new QTimer(this);
    m_timer->setInterval(tickIntervalMs);

    connect(m_timer, &QTimer::timeout, this, &GameManagerBase::tick);
}

bool GameManagerBase::gameRunning() const {
    return m_timer->isActive();
}

void GameManagerBase::startGame() {
    if (!m_timer->isActive()) {
        m_timer->start();
        Q_EMIT gameRunningChanged();
    }
}

void GameManagerBase::stopGame() {
    if (m_timer->isActive()) {
        m_timer->stop();
        Q_EMIT gameRunningChanged();
    }
}

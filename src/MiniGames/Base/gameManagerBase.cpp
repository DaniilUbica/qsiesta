#include "gameManagerBase.h"

using namespace QSiesta::Internal::minigame::base;

GameManagerBase::GameManagerBase(int tickIntervalMs, QObject* parent) : QObject(parent) {
    m_timer = new QTimer(this);
    m_timer->setInterval(tickIntervalMs);
    connect(m_timer, &QTimer::timeout, this, &GameManagerBase::tick);
}

bool GameManagerBase::isRunning() const {
    return m_timer->isActive();
}

void GameManagerBase::startGame() {
    if (!m_timer->isActive()) {
        m_timer->start();
        Q_EMIT runningChanged();
    }
}

void GameManagerBase::stopGame() {
    if (m_timer->isActive()) {
        m_timer->stop();
        Q_EMIT runningChanged();
    }
}

#pragma once

#include "minigamesDefines.h"

#include <QObject>
#include <QUrl>

class QQuickView;

namespace QSiesta::Internal {
namespace minigame {

enum class MiniGame {
    Snake = 0
};

struct MiniGameEntry;

class MiniGamesManager : public QObject {
    Q_OBJECT
public:
    MiniGamesManager(QObject* parent = nullptr);

    void setupContext(QQuickView* view);
    void setCurrentGame(MiniGame game);

    Q_PROPERTY(QUrl qmlSource READ qmlSource NOTIFY currentGameChanged)
    QUrl qmlSource() const { return m_currentSource; }

    Q_SIGNAL void currentGameChanged();

private:
    void registerGame(MiniGame game, const QUrl& qmlSource, QObject* manager);

    std::map<MiniGame, defines::MiniGameEntry> m_games;
    QUrl m_currentSource;
};

} // namespace minigame
} // namespace QSiesta::Internal

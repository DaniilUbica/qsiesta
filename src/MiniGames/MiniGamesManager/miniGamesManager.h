#pragma once

#include <QObject>
#include <QUrl>

#include <list>

class QQuickView;

namespace QSiesta::Internal {
namespace minigame {

namespace base { class GameManagerBase; }

struct MiniGameEntry;

class MiniGamesManager : public QObject {
    Q_OBJECT
public:
    MiniGamesManager(QObject* parent = nullptr);

    void setupContext(QQuickView* view);
    void setCurrentGame(base::GameManagerBase* game);

    void registerGame(base::GameManagerBase* game);
    const std::list<base::GameManagerBase*>& games() const;

    Q_PROPERTY(QUrl qmlSource READ qmlSource NOTIFY currentGameChanged)
    QUrl qmlSource() const { return m_currentSource; }

    Q_SIGNAL void currentGameChanged();

private:
    std::list<base::GameManagerBase*> m_games;
    QUrl m_currentSource;
};

} // namespace minigame
} // namespace QSiesta::Internal

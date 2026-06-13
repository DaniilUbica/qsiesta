#pragma once

#include <QObject>
#include <QTimer>
#include <QQmlContext>

namespace QSiesta::Internal {
namespace minigame::base {

struct MiniGameDescription {
    QUrl qmlSource;
    QString name;
    QString iconName;
};

class GameManagerBase : public QObject {
    Q_OBJECT
public:
    GameManagerBase(int tickIntervalMs, QObject* parent = nullptr);
    virtual ~GameManagerBase() override = default;

    Q_PROPERTY(bool gameRunning READ gameRunning NOTIFY gameRunningChanged)
    bool gameRunning() const;

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();

    Q_SIGNAL void gameRunningChanged();
    Q_SIGNAL void gameOver();

    virtual MiniGameDescription gameDescription() const = 0;
    virtual void setupGameContext(QQmlContext* ctx) = 0;

protected:
    virtual void tick() = 0;

private:
    QTimer* m_timer = nullptr;
};

} // namespace minigame::base
} // namespace QSiesta::Internal

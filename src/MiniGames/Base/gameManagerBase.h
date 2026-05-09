#pragma once

#include <QObject>
#include <QTimer>

namespace QSiesta::Internal {
namespace minigame::base {

class GameManagerBase : public QObject {
    Q_OBJECT
public:
    GameManagerBase(int tickIntervalMs, QObject* parent = nullptr);
    virtual ~GameManagerBase() override = default;

    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)
    bool isRunning() const;

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void stopGame();

    Q_SIGNAL void runningChanged();
    Q_SIGNAL void gameOver();

protected:
    virtual void tick() = 0;

private:
    QTimer* m_timer = nullptr;
};

} // namespace minigame::base
} // namespace QSiesta::Internal

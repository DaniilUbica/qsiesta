#pragma once

#include <QPoint>
#include <QVariantList>

#include <optional>

#include "Base/gameManagerBase.h"

namespace QSiesta::Internal {
namespace minigame::snake {

class GameField;
class Snake;

class GameManager : public minigame::base::GameManagerBase {
    Q_OBJECT
public:
    explicit GameManager(QObject* parent = nullptr);
    ~GameManager() override;

    Q_PROPERTY(QVariantList snakeBody READ snakeBody NOTIFY snakeBodyChanged)
    QVariantList snakeBody() const;
    Q_SIGNAL void snakeBodyChanged();

    Q_PROPERTY(QPoint foodCell READ foodCell NOTIFY foodCellChanged)
    QPoint foodCell() const { return m_foodCell ? *m_foodCell : QPoint { -1, -1 }; }
    Q_SIGNAL void foodCellChanged();

    Q_INVOKABLE unsigned int fieldSize() const;
    Q_INVOKABLE unsigned int cellSize() const;

    Q_INVOKABLE void onKeyPressed(int key);
    Q_INVOKABLE void toInitialState();

protected:
    void tick() override;

    base::MiniGameDescription gameDescription() const override;
    void setupGameContext(QQmlContext* ctx) override;

private:
    void spawnFood();

    std::unique_ptr<GameField> m_field;
    std::unique_ptr<Snake> m_snake;
    std::optional<QPoint> m_foodCell;
};

} // namespace minigame::snake
} // namespace QSiesta::Internal

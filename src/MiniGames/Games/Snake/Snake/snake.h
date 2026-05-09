#pragma once

#include <deque>

#include <QPoint>

namespace QSiesta::Internal {
namespace minigame::snake {

enum class Direction {
    Top = 0,
    Bottom,
    Left,
    Right
};

class Snake final {
public:
    Snake(const QPoint& startPos);

    void tick(bool grow);

    void setDirection(Direction direction);

    [[nodiscard]] QPoint nextHeadPosition() const;

    const QPoint& head() const { return m_body.front(); };
    const QPoint& tail() const { return m_body.back(); };
    const std::deque<QPoint>& body() { return m_body; };

private:
    bool isDirectionAvailable(Direction direction) const;

    std::deque<QPoint> m_body;
    Direction m_direction = Direction::Right;
};

} // namespace minigame::snake
} // namespace QSiesta::Internal
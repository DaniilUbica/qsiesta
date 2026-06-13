#include "snake.h"

using namespace QSiesta::Internal;
using namespace minigame::snake;

Snake::Snake(const QPoint& startPos) {
    m_body.push_front(startPos);
}

void Snake::tick(bool grow) {
    m_body.push_front(nextHeadPosition());
    if (!grow) {
        m_body.pop_back();
    }
}

void Snake::setDirection(Direction direction) {
    if (isDirectionAvailable(direction)) {
        m_direction = direction;
    }
}

QPoint Snake::nextHeadPosition() const {
    const auto yCoeff = m_direction == Direction::Bottom ? 1 : m_direction == Direction::Top ? -1 : 0;
    const auto xCoeff = m_direction == Direction::Right ? 1 : m_direction == Direction::Left ? -1 : 0;

    return { m_body.front().x() + 1 * xCoeff, m_body.front().y() + 1 * yCoeff };
}

bool Snake::isDirectionAvailable(Direction direction) const {
    bool available = m_body.size() == 1 || direction == Direction::Bottom && m_direction != Direction::Top ||
            direction == Direction::Top && m_direction != Direction::Bottom ||
            direction == Direction::Left && m_direction != Direction::Right ||
            direction == Direction::Right && m_direction != Direction::Left;

    return available;
}

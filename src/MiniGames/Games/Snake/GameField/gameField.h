#pragma once

#include <vector>

#include <QPoint>

namespace QSiesta::Internal {
namespace minigame::snake {

enum class Cell {
    Empty = 0,
    Snake,
    Food
};

class GameField final {
public:
    GameField();

    void setCell(const QPoint& pos, Cell cell);
    [[nodiscard]] Cell cell(const QPoint& pos);

    [[nodiscard]] QPoint getRandomEmptyCell();
    [[nodiscard]] bool isPointInField(const QPoint& pos);

private:
    std::vector<Cell> m_cells;
};

} // namespace minigame::snake
} // namespace QSiesta::Internal
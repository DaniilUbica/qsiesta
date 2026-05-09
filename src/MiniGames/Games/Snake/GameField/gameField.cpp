#include "gameField.h"

#include "snakeDefines.h"

#include <QRandomGenerator>

using namespace QSiesta::Internal;
using namespace minigame::snake;

GameField::GameField() {
    m_cells.assign(defines::FIELD_SIZE * defines::FIELD_SIZE, Cell::Empty);
}

void GameField::setCell(const QPoint& pos, Cell cell) {
    m_cells[pos.y() * defines::FIELD_SIZE + pos.x()] = cell;
}

Cell GameField::cell(const QPoint& pos) {
    return m_cells[pos.y() * defines::FIELD_SIZE + pos.x()];
}

QPoint GameField::getRandomEmptyCell() {
    std::vector<int> emptyCells;
    for (int i = 0; i < static_cast<int>(m_cells.size()); ++i) {
        if (m_cells[i] == Cell::Empty) {
            emptyCells.push_back(i);
        }
    }

    if (emptyCells.empty()) {
        return {};
    }

    const int idx = emptyCells[QRandomGenerator::global()->bounded(static_cast<int>(emptyCells.size()))];
    return { idx % static_cast<int>(defines::FIELD_SIZE), idx / static_cast<int>(defines::FIELD_SIZE) };
}

bool GameField::isPointInField(const QPoint& pos) {
    return pos.x() >= 0 && pos.x() < defines::FIELD_SIZE &&
            pos.y() >= 0 && pos.y() < defines::FIELD_SIZE;
}

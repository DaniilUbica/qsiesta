#include "gameManager.h"

#include "GameField/gameField.h"
#include "Snake/snake.h"
#include "snakeDefines.h"

using namespace QSiesta::Internal;
using namespace minigame::snake;

static void initSnakeResources() { Q_INIT_RESOURCE(Snake); }

GameManager::GameManager(QObject* parent) : minigame::base::GameManagerBase(defines::TICK_TIME_MS, parent) {
    initSnakeResources();

    toInitialState();
}

GameManager::~GameManager() {}

void GameManager::tick() {
    if (!m_foodCell) {
        spawnFood();
    }

    const auto newHeadPos = m_snake->nextHeadPosition();
    if (!m_field->isPointInField(newHeadPos)) {
        stopGame();
        Q_EMIT gameOver();
        return;
    }

    const auto newHeadPosCell = m_field->cell(newHeadPos);
    if (newHeadPosCell == Cell::Snake) {
        stopGame();
        Q_EMIT gameOver();
        return;
    }

    const bool snakeAteFood = (newHeadPosCell == Cell::Food);
    if (snakeAteFood) {
        m_foodCell = std::nullopt;
    }
    else {
        m_field->setCell(m_snake->tail(), Cell::Empty);
    }

    m_snake->tick(snakeAteFood);
    m_field->setCell(m_snake->head(), Cell::Snake);

    if (snakeAteFood) {
        spawnFood();
    }

    Q_EMIT snakeBodyChanged();
}

minigame::base::MiniGameDescription GameManager::gameDescription() const {
    static minigame::base::MiniGameDescription desc = {
        .qmlSource = QUrl("qrc:/snake/QMSnakeGame.qml"),
        .name = tr("Snake"),
        .iconName = "snake.svg"
    };

    return desc;
}

void GameManager::setupGameContext(QQmlContext* ctxt) {
    ctxt->setContextProperty("snakeManager", this);
}

void GameManager::spawnFood() {
    m_foodCell = m_field->getRandomEmptyCell();
    m_field->setCell(*m_foodCell, Cell::Food);
    Q_EMIT foodCellChanged();
}

QVariantList GameManager::snakeBody() const {
    const auto& body = m_snake->body();
    QVariantList result;
    result.reserve(static_cast<int>(body.size()));
    for (const QPoint& p : body) {
        result.append(p);
    }
    return result;
}

void GameManager::onKeyPressed(int key) {
    switch (key) {
        case Qt::Key_S:
        case Qt::Key_Down:  m_snake->setDirection(Direction::Bottom); break;
        case Qt::Key_W:
        case Qt::Key_Up:    m_snake->setDirection(Direction::Top);    break;
        case Qt::Key_A:
        case Qt::Key_Left:  m_snake->setDirection(Direction::Left);   break;
        case Qt::Key_D:
        case Qt::Key_Right: m_snake->setDirection(Direction::Right);  break;
        default: return;
    }
}

void GameManager::toInitialState() {
    m_field = std::make_unique<GameField>();

    const auto snakeStartPoint = QPoint(defines::FIELD_SIZE / 2, defines::FIELD_SIZE / 2);
    m_snake = std::make_unique<Snake>(snakeStartPoint);
    m_field->setCell(snakeStartPoint, Cell::Snake);

    spawnFood();

    Q_EMIT snakeBodyChanged();
    Q_EMIT foodCellChanged();
}

unsigned int GameManager::fieldSize() const {
    return defines::FIELD_SIZE;
}

unsigned int GameManager::cellSize() const {
    return defines::CELL_SIZE;
}

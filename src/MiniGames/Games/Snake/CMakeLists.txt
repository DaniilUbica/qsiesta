set(SOURCES
    GameManager/gameManager.cpp
    Snake/snake.cpp
    GameField/gameField.cpp
)

set(HEADERS
    GameManager/gameManager.h
    Snake/snake.h
    GameField/gameField.h
    snakeDefines.h
)

set(RESOURCE
    Snake.qrc
)

add_library(snake STATIC
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE}
)

target_link_libraries(snake PUBLIC minigames-base Qt::Quick Qt::Qml)
target_include_directories(snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

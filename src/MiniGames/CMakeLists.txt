set(SOURCES
    MiniGamesManager/miniGamesManager.cpp
)

set(HEADERS
    MiniGamesManager/miniGamesManager.h
    minigameRegister.hpp
    minigamesDefines.h
)

add_library(minigames-base STATIC
    Base/gameManagerBase.h
    Base/gameManagerBase.cpp
)

target_link_libraries(minigames-base PUBLIC Qt::Core)
target_include_directories(minigames-base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Games/Snake)

add_library(minigames STATIC
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(minigames PUBLIC minigames-base snake Qt::Quick)
target_include_directories(minigames PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

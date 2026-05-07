cmake_minimum_required(VERSION 3.16)

set(Qt6_DIR "/opt/homebrew/Cellar/qt/6.7.3/lib/cmake/Qt6" CACHE PATH "Qt6 CMake config" FORCE)

list(PREPEND CMAKE_PREFIX_PATH
  "/opt/homebrew/Cellar/qt/6.7.3/lib/cmake"
  "/Users/daniilubica/Developer/dev/Qt/Qt6/qt-creator-19.0.0/build/cmake"
)
project(procrastination)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QtCreator REQUIRED COMPONENTS Core)
find_package(Qt6 COMPONENTS Widgets Quick QuickWidgets WebEngineQuick REQUIRED)

set(CREATOR_LIBS
  QtCreator::Core
)

set(TARGET_LIBS
  Qt::Widgets
  Qt::Quick
  Qt::QuickWidgets
  Qt::WebEngineQuick
  QtCreator::ExtensionSystem
  QtCreator::Utils
)

set(SOURCES
  src/procrastination.cpp

  src/NavigationWidget/navigationWidget.cpp
  src/NavigationWidget/navigationWidgetFactory.cpp
)

set(HEADERS
  src/procrastinationConstants.h
  src/procrastinationTr.h

  src/NavigationWidget/navigationWidget.h
  src/NavigationWidget/navigationWidgetFactory.h
)

set(RESOURCE
  src/QMLFiles.qrc
)

add_qtc_plugin(${CMAKE_PROJECT_NAME}
  PLUGIN_DEPENDS
    ${CREATOR_LIBS}
  DEPENDS
    ${TARGET_LIBS}
  SOURCES
    ${SOURCES}
    ${HEADERS}
    ${RESOURCE}
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

get_target_property(QtCreatorCorePath QtCreator::Core LOCATION)

find_program(QtCreatorExecutable
  NAMES
    qtcreator "Qt Creator"
  PATHS
    "${QtCreatorCorePath}/../../../bin"
    "${QtCreatorCorePath}/../../../MacOS"
  NO_DEFAULT_PATH
)

if (QtCreatorExecutable)
  add_custom_target(RunQtCreator
    COMMAND ${QtCreatorExecutable} -pluginpath $<TARGET_FILE_DIR:procrastination>
    DEPENDS procrastination
  )
  set_target_properties(RunQtCreator PROPERTIES FOLDER "qtc_runnable")
endif()

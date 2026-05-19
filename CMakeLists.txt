cmake_minimum_required(VERSION 3.16)

project(qsiesta)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(QtCreator REQUIRED COMPONENTS Core)
find_package(Qt6 COMPONENTS Widgets Quick QuickWidgets REQUIRED)

if (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows")
  find_package(Qt6 COMPONENTS WebEngineQuick REQUIRED)
endif()

set(CREATOR_LIBS
  QtCreator::Core
)

set(TARGET_LIBS
  Qt::Widgets
  Qt::Quick
  Qt::QuickWidgets

  QtCreator::ExtensionSystem
  QtCreator::Utils
)

set(SOURCES
  src/qsiesta.cpp
  src/QSiesta.json

  src/NavigationWidget/navigationWidget.cpp
  src/NavigationWidget/navigationWidgetFactory.cpp
  src/NavigationWidget/viewsModel.cpp
)

set(HEADERS
  src/qsiestaConstants.h
  src/qsiestaTr.h

  src/NavigationWidget/navigationWidget.h
  src/NavigationWidget/navigationWidgetFactory.h
  src/NavigationWidget/viewsModel.h

  src/WebView/webViewRegister.hpp
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
  set(SOURCES
    ${SOURCES}
    src/WebView/macOS/webView.mm
  )

  set(HEADERS
    ${HEADERS}
    src/WebView/macOS/webView.h
  )

  set(TARGET_LIBS
    ${TARGET_LIBS}
    "-framework WebKit"
    "-framework AppKit"
  )

  enable_language(OBJCXX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(TARGET_LIBS
    ${TARGET_LIBS}
    Qt::WebEngineQuick
  )
endif()

set(RESOURCE
  src/QMLFiles.qrc
  src/Resource.qrc
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
    COMMAND ${QtCreatorExecutable} -pluginpath $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    DEPENDS ${CMAKE_PROJECT_NAME}
  )
  set_target_properties(RunQtCreator PROPERTIES FOLDER "qtc_runnable")
endif()

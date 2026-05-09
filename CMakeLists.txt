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

# ── Bundle Qt WebEngine for Linux / Windows ──────────────────────────────────
if (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows")

  # Resolve Qt's bin dir from qmake location
  get_target_property(_qmake Qt6::qmake IMPORTED_LOCATION)
  get_filename_component(_qt_bin "${_qmake}" DIRECTORY)  # e.g. .../Qt/6.x/gcc_64/bin

  if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(_qt_lib     "${_qt_bin}/../lib")
    set(_qt_libexec "${_qt_bin}/../libexec")
    set(_qt_res     "${_qt_bin}/../resources")

    set(_webengine_libs
      "${_qt_lib}/libQt6WebEngineCore.so.6"
      "${_qt_lib}/libQt6WebEngineQuick.so.6"
      "${_qt_lib}/libQt6WebChannel.so.6"
      "${_qt_lib}/libQt6Positioning.so.6"
    )
    set(_webengine_process "${_qt_libexec}/QtWebEngineProcess")

  elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(_qt_lib     "${_qt_bin}")
    set(_qt_res     "${_qt_bin}/../resources")

    set(_webengine_libs
      "${_qt_lib}/Qt6WebEngineCore.dll"
      "${_qt_lib}/Qt6WebEngineQuick.dll"
      "${_qt_lib}/Qt6WebChannel.dll"
      "${_qt_lib}/Qt6Positioning.dll"
    )
    set(_webengine_process "${_qt_lib}/QtWebEngineProcess.exe")
  endif()

  # Shared libraries → next to the plugin
  install(FILES ${_webengine_libs}
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/qtcreator"
  )

  # QtWebEngineProcess → libexec (Qt Creator searches here at runtime)
  install(PROGRAMS "${_webengine_process}"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/libexec/qtcreator"
  )

  # Data files: pak, icudtl.dat
  install(DIRECTORY "${_qt_res}/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/share/qtcreator"
    FILES_MATCHING
      PATTERN "qtwebengine_resources.pak"
      PATTERN "qtwebengine_devtools_resources.pak"
      PATTERN "icudtl.dat"
  )

  # Chromium locale pak files
  install(DIRECTORY "${_qt_bin}/../translations/qtwebengine_locales/"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/share/qtcreator/qtwebengine_locales"
  )

endif()
# ─────────────────────────────────────────────────────────────────────────────

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

add_subdirectory(src/MiniGames)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE minigames)

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

cmake_minimum_required(VERSION 3.14)

project(SpriteUILoader LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Xml UiTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets XMl UiTools)

add_executable(SpriteUILoader
  src/main.cpp
  src/layoutloader.h src/layoutloader.cpp
  src/widgetbuilder.h src/widgetbuilder.cpp
  src/layoutparseerror.h src/layoutparseerror.cpp
)

target_link_libraries(SpriteUILoader
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::UiTools
)

include(GNUInstallDirs)
install(TARGETS SpriteUILoader
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


set_target_properties(SpriteUILoader PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>
    RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin>
)

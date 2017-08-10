cmake_minimum_required(VERSION 2.8.12)

project(GameHall LANGUAGES CXX)

set(Watch_Dir_Path "\"${PROJECT_SOURCE_DIR}/script/QML\"")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message(".................... Project Source Dir is:${Watch_Dir_Path}")

configure_file (
        "${PROJECT_SOURCE_DIR}/src/WatchDirPath.h.in"
        "${PROJECT_BINARY_DIR}/WatchDirPath.h"
)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/WatchAndReload/WatchReload.cpp" "src/WatchAndReload/WatchReload.h" "script/QML/qml.qrc")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)

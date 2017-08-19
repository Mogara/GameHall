cmake_minimum_required(VERSION 2.8.12)

project(GameHall LANGUAGES CXX)

option(DEVELOP_MODE "enable develop mode" OFF)

set(WATCH_DIR_PATH "\"${PROJECT_SOURCE_DIR}/script/QML\"")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(DEV_DIR_PATH "")

message("Project Source Dir is:${WATCH_DIR_PATH}")

configure_file (
        "${PROJECT_SOURCE_DIR}/src/WatchDirPath.h.in"
        "${PROJECT_BINARY_DIR}/WatchDirPath.h"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/DevelopMode.h.in"
	"${PROJECT_BINARY_DIR}/DevelopMode.h"
)

message("${DEVELOP_MODE}")

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/WatchAndReload/WatchReload.cpp" "src/WatchAndReload/WatchReload.h" "script/QML/qml.qrc")

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)

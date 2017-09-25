cmake_minimum_required(VERSION 2.8.12)

project(GameHall LANGUAGES CXX)

option(DEVELOP_MODE "enable develop mode" OFF)
set(WATCH_DIR_PATH "\"${PROJECT_SOURCE_DIR}/script/qml\"")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

message("The source Dir of this project is :${WATCH_DIR_PATH}")

configure_file (
        "${PROJECT_SOURCE_DIR}/src/utils.h.in"
        "${PROJECT_BINARY_DIR}/utils.h"
)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(EXECUTABLE_FILE ${EXECUTABLE_FILE}
    "src/main.cpp"
    "src/watchreload/watchreload.h" "src/watchreload/watchreload.cpp"
    "src/logconsole/logger.h" "src/logconsole/logger.cpp"
    "src/logconsole/qmllive_global.h"
)

if(DEVELOP_MODE)
    add_executable(${PROJECT_NAME} ${EXECUTABLE_FILE})
else()
    add_executable(${PROJECT_NAME} ${EXECUTABLE_FILE} "script/qml/qml.qrc")
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)

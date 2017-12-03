QT += qml quick

CONFIG += c++11

# Enable Precompiled headers (PCH)
CONFIG += precompile_header
PRECOMPILED_HEADER = src/pch.h

INCLUDEPATH += \
    src/application \
    src/common

HEADERS += \
    src/pch.h \
    $$files(src/application/*.h) \
    $$files(src/common/*.h)

SOURCES += \
    src/main.cpp \
    $$files(src/application/*.cpp) \
    $$files(src/common/*.cpp)

RESOURCES += script/qml/qml.qrc

# get the path of qml dir and pass it as macro
WATCH_DIR_PATH = $${_PRO_FILE_PWD_}/script/qml\

CONFIG(develop_mode) {
    DEFINES += DEVELOP_MODE
    DEFINES += "WATCH_DIR_PATH=\\\"$$WATCH_DIR_PATH\\\""
    RESOURCES -= script/qml/qml.qrc
}

# Output a library instead of an application
CONFIG(build_library): DEFINES += MGH_BUILD_LIBRARY

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += qml quick

CONFIG += c++11

HEADERS += src/watchreload/watchreload.h \
           src/logconsole/logger.h \
           src/logconsole/qmllive_global.h \

SOURCES += src/main.cpp \
           src/watchreload/watchreload.cpp \
           src/logconsole/logger.cpp \

RESOURCES += script/qml/qml.qrc

# get the path of qml dir and pass it as macro
WATCH_DIR_PATH = $${_PRO_FILE_PWD_}/script/qml\

!isEmpty(DEVELOP_MODE) {
    DEFINES += "DEVELOP_MODE=1"
    DEFINES += "WATCH_DIR_PATH=\\\"$$WATCH_DIR_PATH\\\""
    RESOURCES -= script/qml/qml.qrc
}

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

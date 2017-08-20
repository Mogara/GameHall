#include <QDebug>
#include <iostream>
#include "watchreload.h"
#include "watchdirpath.h"

WatchReload::WatchReload(QQmlApplicationEngine *engine)
{
    this->engine = engine;
    this->headerObj = this->engine->rootObjects().first()->findChild<QObject*>("header");
    this->contentObj = this->engine->rootObjects().first()->findChild<QObject*>("content");
}

void WatchReload::reload()
{
    qDebug() << "file changes detected";
    if (this->headerObj && this->contentObj) {

        // MACRO set from CMakeLists.txt
        QString contentPath = WATCH_DIR_PATH;
        QString headerPath = WATCH_DIR_PATH;
        headerPath = headerPath.prepend("file:").append("/HeaderComponent.qml");
        contentPath = contentPath.prepend("file:").append("/ContentComponent.qml");

        this->headerObj->setProperty("active",false);
        this->contentObj->setProperty("active",false);
        this->engine->clearComponentCache();
        this->headerObj->setProperty("source",headerPath);
        this->contentObj->setProperty("source",contentPath);
        this->engine->clearComponentCache();
        this->headerObj->setProperty("active",true);
        this->contentObj->setProperty("active",true);

        if (this->headerObj->property("status").toString() == "3"
                || this->contentObj->property("status").toString() == "3") {
            qDebug() << "Some error occured in your code";
            this->headerObj->setProperty("source","");

            // Avoiding incorrectly changes leading it down
            this->contentObj->setProperty("source","qrc:/ErrorComponent.qml");
        } else {
            qDebug() << "Application reloaded successfully";
        }
    } else {
        qDebug() << "No object named header or content";
    }
}

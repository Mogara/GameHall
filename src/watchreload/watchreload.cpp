#include <QDebug>

#include "utils.h"
#include "watchreload.h"

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

        QString contentPath = WATCH_DIR_PATH;
        QString headerPath = WATCH_DIR_PATH;
        QString errorPath = WATCH_DIR_PATH;

        //use absolute path can avoid difference
        headerPath.prepend("file:").append("/HeaderComponent.qml");
        contentPath.prepend("file:").append("/ContentComponent.qml");
        errorPath.prepend("file:").append("/ErrorComponent.qml");

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
            this->contentObj->setProperty("source",errorPath);
        } else {
            qDebug() << "Application reloaded successfully";
        }
    } else {
        qDebug() << "No object named header or content";
    }
}

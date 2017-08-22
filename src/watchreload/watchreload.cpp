#include <QDebug>

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

        this->headerObj->setProperty("active",false);
        this->contentObj->setProperty("active",false);
        this->engine->clearComponentCache();
        this->headerObj->setProperty("source","../script/qml/HeaderComponent.qml");
        this->contentObj->setProperty("source","../script/qml/ContentComponent.qml");
        this->engine->clearComponentCache();
        this->headerObj->setProperty("active",true);
        this->contentObj->setProperty("active",true);

        if (this->headerObj->property("status").toString() == "3"
                || this->contentObj->property("status").toString() == "3") {
            qDebug() << "Some error occured in your code";
            this->headerObj->setProperty("source","");

            // Avoiding incorrectly changes leading it down
            this->contentObj->setProperty("source","../script/qml/ErrorComponent.qml");
        } else {
            qDebug() << "Application reloaded successfully";
        }
    } else {
        qDebug() << "No object named header or content";
    }
}

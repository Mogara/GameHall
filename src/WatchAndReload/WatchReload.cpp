#include <QDebug>
#include "WatchReload.h"
#include "WatchDirPath.h"
#include <iostream>

WatchReload::WatchReload(QQmlApplicationEngine *engine)
{
    this->engine = engine;
    this->headerObj = this->engine->rootObjects().first()->findChild<QObject*>("header");
    this->contentObj = this->engine->rootObjects().first()->findChild<QObject*>("content");
}

void WatchReload::reloadApp()
{
    qDebug() << "file changes detected";
    if (this->headerObj && this->contentObj){
        qDebug() << "start reloading";
        // make use of CMakeLists.txt to recoginize your path in localfilesystem
        QString contentPath = Watch_Dir_Path, headerPath = Watch_Dir_Path;
        headerPath = headerPath.prepend("file:").append("/HeaderComponent.qml");
        contentPath = contentPath.prepend("file:").append("/ContentComponent.qml");

        this->headerObj->setProperty("active",false);
        this->contentObj->setProperty("active",false);

        qDebug() << "1111";

        this->engine->clearComponentCache();
        this->headerObj->setProperty("source",headerPath);
        this->contentObj->setProperty("source",contentPath);
        this->engine->clearComponentCache();

        qDebug() << "1111";

        this->headerObj->setProperty("active",true);
        this->contentObj->setProperty("active",true);

        if (this->headerObj->property("status").toString() == "3" || this->contentObj->property("status").toString() == "3"){
            // another way is to use QScript to check the single script using QQmlComponent::loadUrl function which wastes time
            qDebug() << "Error occured";
            this->headerObj->setProperty("source","");
            // setting loader's source to qrc:/filename.qml will set the ErrorComponent read-only at app's runtime, avoiding incorrectly change leading it down.
            this->contentObj->setProperty("source","qrc:/ErrorComponent.qml");
        }

    }else {
        qDebug() << "not find the first root obj";
    }
}

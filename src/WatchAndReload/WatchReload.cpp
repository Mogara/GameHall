#include <QDebug>
#include "WatchReload.h"
#include "WatchDirPath.h"
#include <iostream>

WatchReload::WatchReload(QQmlApplicationEngine *engine)
{
    this->engine = engine;
    // If the main.qml has an ApplicaitonWindow, it need to findchild called loader
    // else the first rootObjects itself is the loader,can test them according to the name of object
    this->firstrootobj = this->engine->rootObjects().first()->findChild<QObject*>("loader");
}

void WatchReload::reloadApp()
{
    qDebug() << "file changes detected";
    if (this->firstrootobj){
        qDebug() << "start reloading";
        QString path = Watch_Dir_Path;
        path = path.prepend("file:").append("/MainWindow.qml");

        this->firstrootobj->setProperty("active",false);
        this->engine->clearComponentCache();
        this->firstrootobj->setProperty("source",path);
        this->firstrootobj->setProperty("active",true);

        if (this->firstrootobj->property("status").toString() == "3"){
            // another way is to use QScript to check the single script using QQmlComponent::loadUrl function which wastes time
            qDebug() << "Error occured";
            this->firstrootobj->setProperty("source","qrc:/ErrorPage.qml");
        }

    }else {
        qDebug() << "not find the first root obj";
    }
}

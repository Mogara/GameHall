#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFileSystemWatcher>
#include <QDebug>
#include "WatchAndReload/WatchReload.h"
#include "WatchDirPath.h"
#include <iostream>

int main(int argc, char *argv[])
{
    // disable QML cache to prevent the associated bugs from manifesting
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // monitor the resource dir and output the dirname
    QFileSystemWatcher watcher;

    QString str = WATCH_DIR_PATH; // use Cmakelist.txt to pass a macro to this file
    if (!watcher.addPath(str) ){
        qDebug() << "Target path not found";
    }
    else {
        QStringList list = watcher.directories();
        qDebug() << "Watching dir list: "<< list[0].toUtf8().constData();
    }
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    // a function as a slot to receive and react to the signal
    WatchReload Reload(&engine);
    QObject::connect(&watcher,&QFileSystemWatcher::directoryChanged,&Reload,&WatchReload::reload);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFileSystemWatcher>
#include <QDebug>
#include "watchreload/watchreload.h"
#include "utils.h"

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

#if DEVELOP_MODE == ON
    QString devPath = DEVELOP_DIR_PATH;
    qputenv("QT_QUICK_CONTROLS_CONF", (devPath+"/qtquickcontrols2.conf").toUtf8());
    engine.load(QUrl(devPath+"/main.qml"));
#else
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
#endif

    // a function as a slot to receive and react to the signal
    WatchReload Reload(&engine);
    QObject::connect(&watcher,&QFileSystemWatcher::directoryChanged,&Reload,&WatchReload::reload);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

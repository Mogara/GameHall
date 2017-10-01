#include <QDebug>
#include <QFileSystemWatcher>
#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>

#include "logconsole/logger.h"
#include "watchreload/watchreload.h"

// http://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterSingletonType-1
static QObject *logSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

   return Logger::instance();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // register the singleton class to QML engine used to send log message signal
    qmlRegisterSingletonType<Logger>("qmllive.logger", 1, 0, "Logger",logSingletonProvider);

#if defined(DEVELOP_MODE)
    qDebug() << "DEVELOP_MODE=ON";
    // monitor the resource dir and output the dirname
    QFileSystemWatcher filewatcher;
    QString watchPath = WATCH_DIR_PATH; // use Cmakelist.txt to pass a macro to this file
    if (!filewatcher.addPath(watchPath) ){
        qDebug() << "Target watch path not found";
    }
    else {
        QStringList dirList = filewatcher.directories();
        qDebug() << "Watching dir list: "<< dirList[0].toUtf8().constData();
    }
    // disable QML cache to avoid reload twice
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    QString confFilePath = WATCH_DIR_PATH;
    QString mainQmlPath = WATCH_DIR_PATH;
    QString consolePath = WATCH_DIR_PATH;
    confFilePath.append("/qtquickcontrols2.conf");
    mainQmlPath.append("/main.qml");
    consolePath.append("/LogCurtain.qml");

    // use this to load quickcontrol.conf when qml.qrc file is not loaded
    qputenv("QT_QUICK_CONTROLS_CONF", (confFilePath).toUtf8());

    engine.load(QUrl(mainQmlPath));

    QObject *consoleObj = engine.rootObjects().first()->findChild<QObject *>("console");
    consoleObj->setProperty("source",consolePath);

    WatchReload reloader(&engine);
    QObject::connect(&filewatcher,&QFileSystemWatcher::directoryChanged,&reloader,&WatchReload::reload);
#else
    qDebug() << "DEVELOP_MODE=OFF";
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    // make the console and shortcut only available in DEVELOP_MODE
    QObject *showlogObj = engine.rootObjects().first()->findChild<QObject *>("showlog");
    showlogObj->setProperty("enabled",false);
    QObject *clearlogObj = engine.rootObjects().first()->findChild<QObject *>("clearlog");
    clearlogObj->setProperty("enabled",false);
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include "applicationengine.h"

#include "livereloader.h"
#include "logger.h"

#include <QDebug>
#include <QQmlApplicationEngine>

#ifdef DEVELOP_MODE
static QObject *loggerSingletonProvider(QQmlEngine *, QJSEngine *){
   return Logger::instance();
}
#endif // DEVELOP_MODE

class ApplicationEnginePrivate
{
public:
    ApplicationEnginePrivate()
#ifdef DEVELOP_MODE
        : liveReloader(&engine)
#endif // DEVELOP_MODE
    {

    }

    QQmlApplicationEngine engine;

    void init()
    {
#ifdef DEVELOP_MODE
        qDebug() << "DEVELOP_MODE=ON";

        QString configFilePath = FILE_PATH.arg(WATCH_DIR_PATH).arg(CONFIG_FILE);
        QString mainQmlPath = FILE_PATH.arg(WATCH_DIR_PATH).arg(MAIN_QML_FILE);
        QString consolePath = FILE_PATH.arg(WATCH_DIR_PATH).arg(CONSOLE_QML_FILE);

        // use this to load quickcontrol.conf when qml.qrc file is not loaded
        qputenv(QT_QUICK_CONTROLS_CONF, configFilePath.toUtf8());

        engine.load(QUrl(mainQmlPath));

        QObject *console = engine.rootObjects().first()->findChild<QObject *>(CONSOLE_ID);
        console->setProperty(PROPERTY_SOURCE, consolePath);

        liveReloader.beginWatching();
#else
        qDebug() << "DEVELOP_MODE=OFF";
        engine.load(QUrl(DEFAULT_MAIL_QML_PATH));
#endif // DEVELOP_MODE
    }

    void registerQmlTypes()
    {
#ifdef DEVELOP_MODE
        // Register the singleton class to QML engine used to send log message signal
        qmlRegisterSingletonType<Logger>(QML_LOGGER_URI, 1, 0, QML_LOGGER_TYPE_NAME, loggerSingletonProvider);
#endif // DEVELOP_MODE
    }

#ifdef DEVELOP_MODE
    LiveReloader liveReloader;
#endif // DEVELOP_MODE

    static const char *QT_QUICK_CONTROLS_CONF;

    static const QString FILE_PATH;

    static const QString CONFIG_FILE;
    static const QString MAIN_QML_FILE;
    static const QString CONSOLE_QML_FILE;

    static const QString DEFAULT_MAIL_QML_PATH;

    static const QString CONSOLE_ID;

    static const char *PROPERTY_SOURCE;

    static const char *QML_LOGGER_URI;
    static const char *QML_LOGGER_TYPE_NAME;
};

const char *ApplicationEnginePrivate::QT_QUICK_CONTROLS_CONF = "QT_QUICK_CONTROLS_CONF";

const QString ApplicationEnginePrivate::FILE_PATH = "%1/%2";

const QString ApplicationEnginePrivate::CONFIG_FILE = "qtquickcontrols2.conf";
const QString ApplicationEnginePrivate::MAIN_QML_FILE = "main.qml";
const QString ApplicationEnginePrivate::CONSOLE_QML_FILE = "LogConsole.qml";

const QString ApplicationEnginePrivate::DEFAULT_MAIL_QML_PATH = "qrc:/main.qml";

const QString ApplicationEnginePrivate::CONSOLE_ID = "console";

const char *ApplicationEnginePrivate::PROPERTY_SOURCE = "source";

const char *ApplicationEnginePrivate::QML_LOGGER_URI = "qmllive.logger";
const char *ApplicationEnginePrivate::QML_LOGGER_TYPE_NAME = "Logger";

ApplicationEngine::ApplicationEngine()
    : p_ptr(new ApplicationEnginePrivate)
{
    M_P(ApplicationEngine);
    p->registerQmlTypes();
    p->init();
}

ApplicationEngine::~ApplicationEngine()
{
    delete p_ptr;
}

bool ApplicationEngine::hasNoRootObject() const
{
    return p_ptr->engine.rootObjects().isEmpty();
}

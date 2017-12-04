#include "livereloader.h"

#include <QFileSystemWatcher>
#include <QQmlApplicationEngine>
#include <QVariant>

class LiveReloaderPrivate
{
public:
    LiveReloaderPrivate()
        : engine(NULLPTR), headerObject(NULLPTR), contentObject(NULLPTR)
    {

    }

    void reload()
    {
#ifdef DEVELOP_MODE
        if (headerObject != NULLPTR && contentObject != NULLPTR) {

            // Use absolute path to avoid difference
            static QString headerPath = QML_PATH.arg(WATCH_DIR_PATH).arg(HEADER_COMPONENT_NAME);
            static QString contentPath = QML_PATH.arg(WATCH_DIR_PATH).arg(CONTENT_COMPONENT_NAME);
            static QString errorPath = QML_PATH.arg(WATCH_DIR_PATH).arg(ERROR_COMPONENT_NAME);

            headerObject->setProperty(PROPERTY_ACTIVE, false);
            contentObject->setProperty(PROPERTY_ACTIVE, false);
            engine->clearComponentCache();

            headerObject->setProperty(PROPERTY_SOURCE, headerPath);
            contentObject->setProperty(PROPERTY_SOURCE, contentPath);
            engine->clearComponentCache();

            headerObject->setProperty(PROPERTY_ACTIVE, true);
            contentObject->setProperty(PROPERTY_ACTIVE, true);

            if (headerObject->property(PROPERTY_STATUS).toInt() == Error
                    || contentObject->property(PROPERTY_STATUS).toInt() == Error) {
                qDebug() << "Error occured";

                headerObject->setProperty(PROPERTY_SOURCE, QString());

                // Loading error content
                contentObject->setProperty(PROPERTY_SOURCE, errorPath);
            } else {
                qDebug() << "Qml reloaded";
            }
        }
#endif // DEVELOP_MODE
    }

    QQmlApplicationEngine *engine;
    QObject *headerObject;
    QObject *contentObject;

    QFileSystemWatcher fileWatcher;

    enum LoaderStatus { Null, Ready, Loading, Error };

    static const QString HEADER_ID;
    static const QString CONTENT_ID;

    static const QString QML_PATH;

    static const QString HEADER_COMPONENT_NAME;
    static const QString CONTENT_COMPONENT_NAME;
    static const QString ERROR_COMPONENT_NAME;

    static const char *PROPERTY_ACTIVE;
    static const char *PROPERTY_SOURCE;
    static const char *PROPERTY_STATUS;

    static const char *QML_DISABLE_DISK_CACHE;
    static const QByteArray QML_DISABLE_DISK_CACHE_ON;
};

const QString LiveReloaderPrivate::HEADER_ID = "header";
const QString LiveReloaderPrivate::CONTENT_ID = "content";

const QString LiveReloaderPrivate::QML_PATH = "file:%1/%2.qml";

const QString LiveReloaderPrivate::HEADER_COMPONENT_NAME = "HeaderComponent";
const QString LiveReloaderPrivate::CONTENT_COMPONENT_NAME = "ContentComponent";
const QString LiveReloaderPrivate::ERROR_COMPONENT_NAME = "ErrorComponent";

const char *LiveReloaderPrivate::PROPERTY_ACTIVE = "active";
const char *LiveReloaderPrivate::PROPERTY_SOURCE = "source";
const char *LiveReloaderPrivate::PROPERTY_STATUS = "status";

const char *LiveReloaderPrivate::QML_DISABLE_DISK_CACHE = "QML_DISABLE_DISK_CACHE";
const QByteArray LiveReloaderPrivate::QML_DISABLE_DISK_CACHE_ON = "1";

LiveReloader::LiveReloader(QQmlApplicationEngine *engine)
    : p_ptr(new LiveReloaderPrivate)
{
    M_P(LiveReloader);

    p->engine = engine;

    // Disable QML cache to avoid reload twice
    qputenv(p->QML_DISABLE_DISK_CACHE, p->QML_DISABLE_DISK_CACHE_ON);
}

LiveReloader::~LiveReloader()
{
    delete p_ptr;
}

void LiveReloader::beginWatching()
{
#ifdef DEVELOP_MODE
    M_P(LiveReloader);

    p->headerObject = p->engine->rootObjects().first()->findChild<QObject *>(p->HEADER_ID);
    p->contentObject = p->engine->rootObjects().first()->findChild<QObject *>(p->CONTENT_ID);

    // Monitor the resource directory and output the directory name
    QString watchPath = WATCH_DIR_PATH;
    if (!p->fileWatcher.addPath(watchPath)) {
        qDebug() << "Target path not found";
    } else {
        QStringList dirList = p->fileWatcher.directories();
        qDebug() << "Watching dir list: "<< dirList[0];
    }

    QObject::connect(&p->fileWatcher, &QFileSystemWatcher::directoryChanged, [p]{ p->reload(); });
#else
    qFatal("Attempt to watch qml changes outside develop mode!");
#endif // DEVELOP_MODE
}

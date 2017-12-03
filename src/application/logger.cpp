#include "logger.h"

class LoggerPrivate
{
public:

    static Logger *instance;
    static QMutex mutex;
    static bool ignoreMesssages;

    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
    {
        if (!instance) {
            printf("No Logger instance for log message:\n  %s\n", msg.toLatin1().constData());
            abort();
        }

        {
            QMutexLocker l(&mutex);
            if (ignoreMesssages)
                return;
        }

        emit instance->message(type, msg);

        // and output to stdout
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
#endif
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        }
    }
};

Logger *LoggerPrivate::instance = NULLPTR;
QMutex LoggerPrivate::mutex;
bool LoggerPrivate::ignoreMesssages = false;

Logger *Logger::instance()
{
    if (LoggerPrivate::instance == NULLPTR) {
        LoggerPrivate::instance = new Logger();
    }
    return LoggerPrivate::instance;
}

Logger::Logger(QObject *parent) : QObject(parent)
{
    if (LoggerPrivate::instance) {
        qFatal("Cannot create more than one Logger");
    }
    LoggerPrivate::instance = this;

    qInstallMessageHandler(LoggerPrivate::messageHandler);
}

Logger::~Logger()
{
    delete p_ptr;
    qInstallMessageHandler(NULLPTR);
}

void Logger::setIgnoreMessages(bool ignoreMessages)
{
    QMutexLocker l(&LoggerPrivate::mutex);
    LoggerPrivate::ignoreMesssages = ignoreMessages;
}

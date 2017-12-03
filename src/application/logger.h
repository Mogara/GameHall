#ifndef LOGGER_H
#define LOGGER_H

#include "global.h"

#include <QObject>

class LoggerPrivate;

class MGH_EXPORT Logger : public QObject
{
    Q_OBJECT

public:
    ~Logger();

    static Logger *instance();

public slots:
    static void setIgnoreMessages(bool ignoreMessages);

signals:
    void message(int type, const QString &msg, const QUrl &url = QUrl(), int line = -1, int column = -1);

private:
    MGH_DECLARE_PRIVATE(Logger)

    explicit Logger(QObject *parent = NULLPTR);

    LoggerPrivate *p_ptr;
};

#endif // LOGGER_H

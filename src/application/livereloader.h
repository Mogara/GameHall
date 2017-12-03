#ifndef LIVERELOADER_H
#define LIVERELOADER_H

#include "global.h"

class QQmlApplicationEngine;

class LiveReloaderPrivate;

class MGH_EXPORT LiveReloader
{
public:
    LiveReloader(QQmlApplicationEngine *engine);
    ~LiveReloader();

    void beginWatching();

private:
    MGH_DECLARE_PRIVATE(LiveReloader)

    LiveReloaderPrivate *p_ptr;
};

#endif // LIVERELOADER_H

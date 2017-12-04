#ifndef APPLICATION_H
#define APPLICATION_H

#include "global.h"

class ApplicationPrivate;

class MGH_EXPORT Application
{
public:
    Application(int &argc, char **argv);
    ~Application();

    static int exec();

private:
    MGH_DECLARE_PRIVATE(Application)

    ApplicationPrivate *p_ptr;
};

#endif // APPLICATION_H

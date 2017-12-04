#ifndef APPLICATIONENGINE_H
#define APPLICATIONENGINE_H

#include "global.h"

class ApplicationEnginePrivate;

class MGH_EXPORT ApplicationEngine
{
public:
    ApplicationEngine();
    ~ApplicationEngine();

    bool hasNoRootObject() const;

private:
    MGH_DECLARE_PRIVATE(ApplicationEngine)

    ApplicationEnginePrivate *p_ptr;
};

#endif // APPLICATIONENGINE_H

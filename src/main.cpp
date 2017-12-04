#include "application.h"
#include "applicationengine.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    ApplicationEngine engine;
    if (engine.hasNoRootObject())
        return -1;

    return app.exec();
}

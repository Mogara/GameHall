#include "application.h"

#include <QGuiApplication>

class ApplicationPrivate
{
public:
    ApplicationPrivate(int &argc, char **argv)
        : application(argc, argv)
    {

    }

    QGuiApplication application;
};

Application::Application(int &argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    p_ptr = new ApplicationPrivate(argc, argv);
}

Application::~Application()
{
    delete p_ptr;
}

int Application::exec()
{
    return QGuiApplication::exec();
}

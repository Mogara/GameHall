#ifndef WatchReload_H
#define WatchReload_H
#include <QQmlApplicationEngine>

class WatchReload: public QObject
{
    Q_OBJECT
public:
  WatchReload(QQmlApplicationEngine *engine);
public slots:
  void reloadApp();
private:
  QQmlApplicationEngine *engine;
  QObject *headerObj;
  QObject *contentObj;
};

#endif

#ifndef WORKERTHREADPOOL_H
#define WORKERTHREADPOOL_H

#include <QtGlobal>
#include <QObject>
#include <QMap>
#include <QPair>
#include <QThread>
#include "Worker.h"

class WorkerThreadPool : public QObject {

    Q_OBJECT

    private:

    quint32 maxThreadCount;
    quint32 roundRobinCount;

    bool isThreadsStarted;

    QMap<quint32, QPair<QThread*, Worker*>> workers;

    public:
        explicit WorkerThreadPool(QObject *parent = nullptr);

        ~WorkerThreadPool();

        bool startThreads();

        bool stopThreads();

        bool setMaxThreadCount(const quint32 maxThreadCount);

    signals:


};

#endif // WORKERTHREADPOOL_H

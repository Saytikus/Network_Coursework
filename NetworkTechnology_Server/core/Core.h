#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QtGlobal>

#include "storage/data/AccountBufferPool.h"
#include "network/NetworkWorker.h"
#include "core/workers/WorkerThreadPool.h"

class Core : public QObject {

    Q_OBJECT

    private:

        AccountBufferPool *bufferPool;

        QThread *networkThread;

        NetworkWorker *netWorker;

        WorkerThreadPool *workerPool;

    private slots:

    public:
        explicit Core(QObject *parent = nullptr);

        ~Core();

        void initNetwork();

        void initLogic();

    public slots:

    signals:

};

#endif // CORE_H

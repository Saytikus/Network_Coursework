#include "WorkerThreadPool.h"

#include "common/logs/Logger.h"

WorkerThreadPool::WorkerThreadPool(QObject *parent)
    : QObject{parent}
{
    this->maxThreadCount = 4;
    this->roundRobinCount = 0;
    this->isThreadsStarted = false;
}

WorkerThreadPool::~WorkerThreadPool() {

    for(QPair<QThread*, Worker*> workerPair : this->workers) {

        workerPair.first->quit();
        workerPair.first->wait();

        delete workerPair.second;
    }

}

bool WorkerThreadPool::startThreads() {

    if(this->isThreadsStarted) {
        return false;
    }

    quint32 currentThreadNumber = 1;
    for(quint32 i = 0; i < this->maxThreadCount; i++) {

        QThread *thread = new QThread();

        thread->setObjectName("Worker thread №" + QString::number(currentThreadNumber));

        Worker *worker = new Worker(i);
        worker->moveToThread(thread);
        Logger::INSTANCE()->recordLog("WorkerThreadPool", "Worker запущен в потоке " + worker->thread()->objectName());

        QObject::connect(this, &WorkerThreadPool::workRequested, worker, &Worker::doWork);

        this->workers.insert(currentThreadNumber, QPair<QThread*, Worker*>(thread, worker));

        thread->start();

        currentThreadNumber++;
    }

    this->isThreadsStarted = true;

    return true;
}

bool WorkerThreadPool::stopThreads() {

    if(!this->isThreadsStarted) {
        return false;
    }


    for(quint32 workerId : this->workers.keys()) {

        // Останавливаем поток рабочего
        this->workers.value(workerId).first->quit();
        this->workers.value(workerId).first->wait();

        // Очищаем память от рабочего
        delete this->workers.value(workerId).second;

        // Удаляем рабочего из списка
        this->workers.remove(workerId);
    }

    this->isThreadsStarted = false;

    return true;
}

bool WorkerThreadPool::setMaxThreadCount(const quint32 maxThreadCount) {

    if(this->isThreadsStarted) {
        return false;
    }

    this->maxThreadCount = maxThreadCount;

    return true;
}

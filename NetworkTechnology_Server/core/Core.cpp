#include "Core.h"

#include "common/logs/Logger.h"
#include "network/ApplicationServer.h"

#include <QThread>
#include "storage/data/AccountBufferPool.h"

Core::Core(QObject *parent)
    : QObject{parent}
{
    AccountBufferPool::INSTANCE();

    this->netWorker = nullptr;

    this->networkThread = nullptr;

    this->workerPool = new WorkerThreadPool();
}

Core::~Core() {

    delete workerPool;

    networkThread->quit();
    networkThread->wait();

    netWorker->deleteLater();
}

void Core::initNetwork() {


    ApplicationServer *server = new ApplicationServer();

    this->netWorker = new NetworkWorker(server);


    this->networkThread = new QThread();
    this->networkThread->setObjectName("Network Thread");

    this->netWorker->moveToThread(this->networkThread);

    QObject::connect(networkThread, &QThread::finished, netWorker, &NetworkWorker::finished);
    QObject::connect(networkThread, &QThread::finished, networkThread, &QThread::deleteLater);
    QObject::connect(netWorker, &NetworkWorker::finished, networkThread, &QThread::deleteLater);

    this->networkThread->start();


    //QObject::connect(this->netWorker, &NetworkWorker::requestRegisterConnection, this->bufferPool, &AccountBufferPool::registerAccountBuffer, Qt::DirectConnection);
    //QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferRegistered, this->netWorker, &NetworkWorker::addPendingConnection, Qt::DirectConnection);
    //QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferAlreadyExists, this->netWorker, &NetworkWorker::rejectPendingConnection, Qt::DirectConnection);

}

void Core::initLogic() {

    this->workerPool->setMaxThreadCount(2);

    this->workerPool->startThreads();
}

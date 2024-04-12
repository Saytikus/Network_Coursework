#include "Core.h"

#include "common/logs/Logger.h"
#include "network/ApplicationServer.h"

#include <QThread>

#include "core/storage/database/DatabaseReader.h"
#include "core/storage/database/DatabaseWriter.h"

#include "common/const/FilePathConstants.h"

Core::Core(QObject *parent)
    : QObject{parent}
{
    this->bufferPool = new AccountBufferPool();

    this->netWorker = nullptr;

    this->networkThread = nullptr;

    this->workerPool = new WorkerThreadPool();
}

Core::~Core() {

    delete bufferPool;

    delete netWorker;

    networkThread->quit();
    networkThread->wait();
}

void Core::initNetwork() {

    //qRegisterMetaType<QHostAddress>("QHostAddress");


    this->netWorker = new NetworkWorker();

    ApplicationServer *server = new ApplicationServer();

    this->netWorker->setServer(server);


    this->networkThread = new QThread();
    this->networkThread->setObjectName("Network Thread");

    this->netWorker->moveToThread(this->networkThread);

    connect(networkThread, &QThread::finished, netWorker, &QObject::deleteLater);

    this->networkThread->start();


    QObject::connect(this->netWorker, &NetworkWorker::requestRegisterConnection, this->bufferPool, &AccountBufferPool::registerAccountBuffer, Qt::DirectConnection);
    QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferRegistered, this->netWorker, &NetworkWorker::addPendingConnection, Qt::DirectConnection);
    QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferAlreadyExists, this->netWorker, &NetworkWorker::rejectPendingConnection, Qt::DirectConnection);

}

void Core::initLogic() {

    this->workerPool->setMaxThreadCount(4);

    this->workerPool->startThreads();

}

#include "Core.h"

#include "network/ApplicationServer.h"

#include <QThread>

Core::Core(QObject *parent)
    : QObject{parent}
{
    this->bufferPool = new AccountBufferPool();
    this->netWorker = new NetworkWorker();
}

void Core::initNetwork() {

    ApplicationServer *server = new ApplicationServer();

    this->netWorker->setServer(server);

    QObject::connect(this->netWorker, &NetworkWorker::requestRegisterConnection, this->bufferPool, &AccountBufferPool::registerAccountBuffer);
    QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferRegistered, this->netWorker, &NetworkWorker::addPendingConnection);
    QObject::connect(this->bufferPool, &AccountBufferPool::accountBufferAlreadyExists, this->netWorker, &NetworkWorker::rejectPendingConnection);

}

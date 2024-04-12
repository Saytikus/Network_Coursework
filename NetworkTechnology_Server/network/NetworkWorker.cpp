#include "NetworkWorker.h"

#include "common/logs/Logger.h"



NetworkWorker::~NetworkWorker() {
    Logger::recordLog("NetworkWorker", "Зашли в деструктор NetworkWorker");

    //delete server;
}

NetworkWorker::NetworkWorker(ApplicationServer *server, QObject *parent)
    : QObject{parent}
{
    this->setServer(server);
}

void NetworkWorker::setServer(ApplicationServer *server) {

    mutex.lock();

    this->server = server;

    if(!server->getIsInitialised()) {
        // TODO: значения из статик настроек
        server->init(QHostAddress::Any, 51353);
    }

    if(!server->getIsListening()) {
        server->start();
    }

    QObject::connect(server, &ApplicationServer::messageReceived, this, &NetworkWorker::messageReceived, Qt::QueuedConnection);
    QObject::connect(server, &ApplicationServer::requestRegisterConnection, this, &NetworkWorker::requestRegisterConnection, Qt::QueuedConnection);

    mutex.unlock();
}

void NetworkWorker::sendMessage(const QByteArray message, NetworkAddressData networkAddress) {

    mutex.lock();

    this->server->send(message, networkAddress);

    mutex.unlock();
}

void NetworkWorker::addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket) {

    mutex.lock();

    this->server->addPendingConnection(networkData, pendingSocket);

    mutex.unlock();
}

void NetworkWorker::rejectPendingConnection(const QTcpSocket* pendingSocket) {

    mutex.lock();

    this->server->rejectPendingConnection(pendingSocket);

    mutex.unlock();
}

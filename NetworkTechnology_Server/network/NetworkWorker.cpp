#include "NetworkWorker.h"

NetworkWorker::NetworkWorker(ApplicationServer *server, QObject *parent)
    : QObject{parent}
{
    this->server = server;

    if(!server->getIsListening()) {
        server->start();
    }

    QObject::connect(server, &ApplicationServer::messageReceived, this, &NetworkWorker::messageReceived);
    QObject::connect(server, &ApplicationServer::requestRegisterConnection, this, &NetworkWorker::requestRegisterConnection);
}

void NetworkWorker::sendMessage(const QByteArray message, NetworkAddressData networkAddress) {
    this->server->send(message, networkAddress);
}

void NetworkWorker::addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket) {
    this->server->addPendingConnection(networkData, pendingSocket);
}

void NetworkWorker::rejectPendingConnection(const QTcpSocket* pendingSocket) {
    this->server->rejectPendingConnection(pendingSocket);
}
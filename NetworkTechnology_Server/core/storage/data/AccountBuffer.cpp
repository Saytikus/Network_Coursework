#include "AccountBuffer.h"


AccountBuffer::AccountBuffer(const quint32 initId, const NetworkAddressData initNetworkData, QByteArray *initSendBuffer, QByteArray *initReadBuffer, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
    this->networkData = initNetworkData;
    this->sendBuffer.setBuffer(initSendBuffer);
    this->readBuffer.setBuffer(initReadBuffer);
}

quint32 AccountBuffer::getId() const {
    return id;
}

NetworkAddressData AccountBuffer::getNetworkData() const {
    return networkData;
}

void AccountBuffer::setNetworkData(const NetworkAddressData newNetworkData) {
    networkData = newNetworkData;
}

void AccountBuffer::writeSendBuffer(const QByteArray data, const qint32 size) {
    this->sendBuffer.open(QIODevice::WriteOnly);

    this->sendBuffer.write(data, size);

    this->sendBuffer.close();
}

void AccountBuffer::writeReadBuffer(const QByteArray data, const qint32 size) {
    this->readBuffer.open(QIODevice::WriteOnly);

    this->readBuffer.write(data, size);

    this->readBuffer.close();
}

QByteArray AccountBuffer::getSendBuffer() const {
    return sendBuffer.buffer();
}

QByteArray AccountBuffer::getReadBuffer() const {
    return readBuffer.buffer();
}

void AccountBuffer::clearSendBuffer() {
    this->sendBuffer.buffer().clear();
}

void AccountBuffer::clearReadBuffer() {
    this->readBuffer.buffer().clear();
}


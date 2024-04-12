#include "AccountBuffer.h"



AccountBuffer::AccountBuffer(const quint32 initId, const NetworkAddressData initNetworkData, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
    this->networkData = initNetworkData;
    this->sendBuffer = QList<QByteArray>();
    this->readBuffer = QList<QByteArray>();

    this->hasSendData = false;
    this->hasReadData = false;
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

    if(data.isEmpty() || data.isNull()) {
        return;
    }

    this->sendBuffer.append(data);

    if(!this->hasSendData) {
        this->hasSendData = true;
    }
}

void AccountBuffer::writeReadBuffer(const QByteArray data, const qint32 size) {

    if(data.isEmpty() || data.isNull()) {
        return;
    }

    this->readBuffer.append(data);

    if(!this->hasReadData) {
        this->hasReadData = true;
    }
}

QList<QByteArray> AccountBuffer::getSendBuffer() const {
    return sendBuffer;
}

QList<QByteArray> AccountBuffer::getReadBuffer() const {
    return readBuffer;
}

void AccountBuffer::clearSendBuffer() {
    this->sendBuffer.clear();
}

void AccountBuffer::clearReadBuffer() {
    this->readBuffer.clear();
}

QByteArray AccountBuffer::takeSendData() {
    if(this->hasSendData) {

        if(this->sendBuffer.size() == 1) {
            this->hasSendData = false;
        }

        return this->sendBuffer.takeFirst();

    }

}

QByteArray AccountBuffer::takeReadData() {
    if(this->hasReadData) {

        if(this->readBuffer.size() == 1) {
            this->hasReadData = false;
        }

        return this->readBuffer.takeFirst();

    }
}

bool AccountBuffer::getHasReadData() const
{
    return hasReadData;
}

bool AccountBuffer::getHasSendData() const
{
    return hasSendData;
}

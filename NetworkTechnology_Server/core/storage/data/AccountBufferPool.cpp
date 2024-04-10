#include "AccountBufferPool.h"

#include "common/logs/Logger.h"

AccountBufferPool::AccountBufferPool(QObject *parent)
    : QObject{parent}
{
    this->lastAccountBufferId = 0;
}

AccountBufferPool::~AccountBufferPool() {
    qDeleteAll(this->accountBuffers);
}

void AccountBufferPool::registerAccountBuffer(const QHostAddress address, const quint16 port, const QTcpSocket* pendingSocket) {

    NetworkAddressData netData(address, port);



    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getNetworkData() == netData) {

            emit accountBufferAlreadyExists(pendingSocket);

            return ;

        }

    }



    AccountBuffer *newAccountBuffer = new AccountBuffer(++this->lastAccountBufferId, netData, new QByteArray(), new QByteArray());

    newAccountBuffer->clearSendBuffer();
    newAccountBuffer->clearReadBuffer();

    this->accountBuffers.append(newAccountBuffer);



    Logger::recordLog("AccountBufferPool", "Зарегистрирован новый буфер! [" + QString::number(newAccountBuffer->getId()) + " " + address.toString() + ":" + QString::number(port) + "]");

    emit accountBufferRegistered(netData, pendingSocket);
}

void AccountBufferPool::writeSendBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeSendBuffer(data, size);

            QByteArray bufferData(buffer->getSendBuffer());

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Записано в буфер отправки [" + QString::number(accountBufferId) + "]: " + data);

            emit sendBufferChanged(bufferData, accountBufferId);
        }

    }

}

void AccountBufferPool::writeReadBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeReadBuffer(data, size);

            QByteArray bufferData(buffer->getReadBuffer());

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Записано в буфер чтения [" + QString::number(accountBufferId) + "]: " + data);

            emit readBufferChanged(bufferData, accountBufferId);
        }

    }

}

void AccountBufferPool::clearSendBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->clearSendBuffer();

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Буфер отправки очищен [" + QString::number(accountBufferId) + "]");

            emit sendBufferChanged(QByteArray(), accountBufferId);
        }

    }

}

void AccountBufferPool::clearReadBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->clearReadBuffer();

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Буфер чтения очищен [" + QString::number(accountBufferId) + "]");

            emit readBufferChanged(QByteArray(), accountBufferId);
        }

    }

}

void AccountBufferPool::deleteAccountBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            // Удаляем буфер из списка
            this->accountBuffers.removeOne(buffer);

            // Очищаем память от буфера
            delete buffer;

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Удалён буфер [" + QString::number(accountBufferId) + "]");
        }

    }

}

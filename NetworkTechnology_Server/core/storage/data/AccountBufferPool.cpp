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

void AccountBufferPool::registerAccountBuffer(const QHostAddress address, const quint16 port) {

    AccountBuffer *newAccountBuffer = new AccountBuffer(++this->lastAccountBufferId, NetworkAddressData(address, port), new QByteArray(), new QByteArray());

    newAccountBuffer->clearSendBuffer();
    newAccountBuffer->clearReadBuffer();

    this->accountBuffers.append(newAccountBuffer);

    Logger::recordLog("AccountBufferPool", "Зарегистрирован новый буфер! [" + QString::number(newAccountBuffer->getId()) + " " + address.toString() + ":" + QString::number(port) + "]");

}

void AccountBufferPool::writeSendBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeSendBuffer(data, size);

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Записано в буфер отправки [" + QString::number(accountBufferId) + "]: " + data);
        }

    }

}

void AccountBufferPool::writeReadBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    for(AccountBuffer *buffer : this->accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeReadBuffer(data, size);

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Записано в буфер чтения [" + QString::number(accountBufferId) + "]: " + data);
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

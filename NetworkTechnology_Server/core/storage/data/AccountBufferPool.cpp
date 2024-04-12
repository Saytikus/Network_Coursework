#include "AccountBufferPool.h"

#include "common/logs/Logger.h"



AccountBufferPool* AccountBufferPool::instance = 0;
QMutex AccountBufferPool::mutex;

quint32 AccountBufferPool::lastAccountBufferId = 0;

bool AccountBufferPool::hasReadPacket = false;
bool AccountBufferPool::hasSendPacket = false;

QList<AccountBuffer*> AccountBufferPool::accountBuffers = QList<AccountBuffer*>();



AccountBufferPool::AccountBufferPool(QObject *parent)
    : QObject{parent}
{
    // NO-OP
}

AccountBufferPool::~AccountBufferPool() {

    Logger::recordLog("AccountBufferPool", "Зашли в деструктор AccountBufferPool");

    if(!this->accountBuffers.isEmpty()) {
        qDeleteAll(this->accountBuffers);
    }

    if(instance) {
        delete AccountBufferPool::instance;
    }

}

void AccountBufferPool::registerAccountBuffer(QHostAddress address, quint16 port, QTcpSocket* pendingSocket) {

    NetworkAddressData netData(address, port);

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getNetworkData() == netData) {

            emit instance->accountBufferAlreadyExists(pendingSocket);

            return ;

        }

    }


    mutex.lock();

    AccountBuffer *newAccountBuffer = new AccountBuffer(++lastAccountBufferId, netData);

    newAccountBuffer->clearSendBuffer();
    newAccountBuffer->clearReadBuffer();

    AccountBufferPool::accountBuffers.append(newAccountBuffer);

    mutex.unlock();

    Logger::INSTANCE()->recordLog("AccountBufferPool", "Зарегистрирован новый буфер! [" + QString::number(newAccountBuffer->getId()) + " " + address.toString() + ":" + QString::number(port) + "]");

    emit instance->accountBufferRegistered(netData, pendingSocket);
}

void AccountBufferPool::writeSendBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    if(data.isEmpty() || data.isNull() || size <= 0) {
        return;
    }

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeSendBuffer(data, size);

            hasSendPacket = true;

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Записано в буфер отправки [" + QString::number(accountBufferId) + "]: " + data);

        }

    }

}

void AccountBufferPool::writeReadBuffer( const quint32 accountBufferId, const QByteArray data, const qint32 size) {

    if(data.isEmpty() || data.isNull() || size <= 0) {
        return;
    }

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->writeReadBuffer(data, size);

            hasReadPacket = true;

            mutex.unlock();

            Logger::INSTANCE()->recordLog("AccountBufferPool", "Записано в буфер чтения [" + QString::number(accountBufferId) + "]: " + data);

        }

    }

}

void AccountBufferPool::clearSendBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->clearSendBuffer();

            mutex.unlock();

            Logger::INSTANCE()->recordLog("AccountBufferPool", "Буфер отправки очищен [" + QString::number(accountBufferId) + "]");

        }

    }

}

void AccountBufferPool::clearReadBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            buffer->clearReadBuffer();

            mutex.unlock();

            Logger::INSTANCE()->recordLog("AccountBufferPool", "Буфер чтения очищен [" + QString::number(accountBufferId) + "]");

        }

    }

}

void AccountBufferPool::deleteAccountBuffer(const quint32 accountBufferId) {

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getId() == accountBufferId) {

            mutex.lock();

            // Удаляем буфер из списка
            accountBuffers.removeOne(buffer);

            // Очищаем память от буфера
            delete buffer;

            mutex.unlock();

            Logger::INSTANCE()->recordLog("AccountBufferPool", "Удалён буфер [" + QString::number(accountBufferId) + "]");
        }

    }

}

QByteArray AccountBufferPool::takeSendPacket() {

    if(!hasSendPacket) {
        return QByteArray();
    }

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getHasSendData()) {

            mutex.lock();

            QByteArray formedPacket = buffer->takeSendData();

            quint32 bufferId = buffer->getId();

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Взят пакет на отправку из буфера " + QString::number(bufferId) + " Пакет: " + formedPacket);

            calculateHasSendPacket();

            return formedPacket;
        }

    }

    return QByteArray();

}

QByteArray AccountBufferPool::takeReadPacket() {

    if(!hasReadPacket) {
        return QByteArray();
    }

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getHasReadData()) {

            mutex.lock();

            QByteArray networkPacket = buffer->takeReadData();

            quint32 bufferId = buffer->getId();

            mutex.unlock();

            Logger::recordLog("AccountBufferPool", "Взят пакет на обработку из буфера " + QString::number(bufferId) + " Пакет: " + networkPacket);

            calculateHasReadPacket();

            return networkPacket;
        }

    }

    return QByteArray();
}

void AccountBufferPool::calculateHasReadPacket() {

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getHasReadData()) {

            mutex.lock();

            hasReadPacket = true;

            mutex.unlock();

            return ;
        }

    }

    hasReadPacket = false;
}

void AccountBufferPool::calculateHasSendPacket() {

    for(AccountBuffer *buffer : accountBuffers) {

        if(buffer->getHasSendData()) {

            mutex.lock();

            hasSendPacket = true;

            mutex.unlock();

            return ;
        }

    }

    hasSendPacket = false;
}

bool AccountBufferPool::getHasReadPacket()
{
    return hasReadPacket;
}

bool AccountBufferPool::getHasSendPacket()
{
    return hasSendPacket;
}

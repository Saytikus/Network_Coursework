#include "Worker.h"

#include "common/enums/EnumHandlerType.h"
#include "core/handlers/AccountRegistrationHandler.h"
#include <QDataStream>



Worker::Worker(const quint32 initId, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
}


void Worker::doWork(QByteArray packet) {

    QDataStream readStream(&packet, QIODevice::ReadOnly);

    EnumHandlerType commandType;

    readStream >> commandType;

    BasePacket innerPacket = this->serializerPool.getSerializer(commandType).deserialize(commandType, packet);

    this->handlerPool.getHandler(commandType).handle(innerPacket);

}

quint32 Worker::getId() const
{
    return id;
}


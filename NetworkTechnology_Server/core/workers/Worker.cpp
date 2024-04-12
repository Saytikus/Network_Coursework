#include "Worker.h"

#include "common/enums/EnumHandlerType.h"
#include <QDataStream>

#include "core/storage/data/AccountBufferPool.h"
#include "common/logs/Logger.h"
#include <QThread>

Worker::Worker(const quint32 initId, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
}


void Worker::doWork() {

    // Бесконечно выполняем работу
    while(true) {        

        // Если в пуле буферов есть пакет на обработку
        if(AccountBufferPool::INSTANCE()->getHasReadPacket()) {

            //Logger::recordLog("Worker", "Я - рабочий №" + QThread::currentThread()->objectName() + ", НАШЕЛ РАБОТУ");

            // Берем пакет
            QByteArray packet = AccountBufferPool::INSTANCE()->takeReadPacket();

            // Считываем тип команды
            QDataStream readStream(&packet, QIODevice::ReadOnly);
            EnumHandlerType commandType;
            readStream >> commandType;

            // Десериализуем пакет во внутренний
            BasePacket innerPacket = this->serializerPool.getSerializer(commandType).deserialize(commandType, packet);

            // Обрабатываем пакет
            this->handlerPool.getHandler(commandType).handle(innerPacket);
        }
    }

}

quint32 Worker::getId() const
{
    return id;
}


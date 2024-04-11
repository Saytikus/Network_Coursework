#include "SerializerPool.h"

#include "AccountRegistrationSerializer.h""

SerializerPool::SerializerPool(QObject *parent) : QObject{parent} {

    this->serializers.insert(EnumHandlerType::AccountRegistration, AccountRegistrationSerializer());

}

BaseSerializer SerializerPool::getSerializer(const EnumHandlerType commandType) {

    if(!this->serializers.contains(commandType)) {
        // TODO: свой эксепшен
        throw std::runtime_error("Запрашиваемый обработчик не найден");
    }

    return this->serializers.value(commandType);
}

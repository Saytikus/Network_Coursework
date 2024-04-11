#include "HandlerPool.h"

#include "AccountRegistrationHandler.h"

HandlerPool::HandlerPool(QObject *parent) : QObject{parent} {

    this->handlers.insert(EnumHandlerType::AccountRegistration, AccountRegistrationHandler());

}

BaseHandler HandlerPool::getHandler(const EnumHandlerType handlerType) {
    if(!this->handlers.contains(handlerType)) {
        // TODO: свой эксепшен
        throw std::runtime_error("Запрашиваемый обработчик не найден");
    }

    return this->handlers.value(handlerType);
}

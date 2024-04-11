#include "AccountRegistrationHandler.h"


EnumHandlerType AccountRegistrationHandler::BaseHandler::handlerType = EnumHandlerType::AccountRegistration;


AccountRegistrationHandler::AccountRegistrationHandler(QObject *parent)
    : QObject{parent}
{

}

void AccountRegistrationHandler::handle(BasePacket packet) {
    // TODO: действия для регистрации аккаунта
}

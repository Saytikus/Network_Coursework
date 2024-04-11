#include "AccountRegistrationSerializer.h"

AccountRegistrationSerializer::AccountRegistrationSerializer()
{
    // NO-OP
}

QByteArray AccountRegistrationSerializer::serialize(BasePacket innerPacket) {
    // TODO: метод и не забыть проверку на код пакета

    return QByteArray();
}

BasePacket AccountRegistrationSerializer::deserialize(EnumHandlerType serializerType, QByteArray serializedPacket)  {
    //TODO: метод

    return BasePacket();
}

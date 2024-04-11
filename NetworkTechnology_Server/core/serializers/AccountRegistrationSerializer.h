#ifndef ACCOUNTREGISTRATIONSERIALIZER_H
#define ACCOUNTREGISTRATIONSERIALIZER_H

#include "BaseSerializer.h"

class AccountRegistrationSerializer : public BaseSerializer {


    public:
        AccountRegistrationSerializer();

        virtual QByteArray serialize(BasePacket innerPacket) override;

        virtual BasePacket deserialize(EnumHandlerType serializerType, QByteArray serializedPacket) override;
};

#endif // ACCOUNTREGISTRATIONSERIALIZER_H

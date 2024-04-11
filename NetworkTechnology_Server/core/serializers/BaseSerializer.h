#ifndef BASESERIALIZER_H
#define BASESERIALIZER_H

#include <QtGlobal>
#include <QByteArray>
#include "core/storage/innerPackets/BasePacket.h"
#include "common/enums/EnumHandlerType.h"

class BaseSerializer {

    protected:
        static EnumHandlerType serializerType;

    public:

        virtual QByteArray serialize(BasePacket innerPacket) {};

        virtual BasePacket deserialize(EnumHandlerType serializerType, QByteArray serializedPacket) {};

        static EnumHandlerType getSerializerType();
};

inline EnumHandlerType BaseSerializer::getSerializerType()
{
    return serializerType;
}

#endif // BASESERIALIZER_H

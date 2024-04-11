#ifndef BASEPACKET_H
#define BASEPACKET_H

#include "common/enums/EnumHandlerType.h"

class BasePacket {

    protected:
        static EnumHandlerType packetType;

    public:

        static EnumHandlerType getPacketType();
};

inline EnumHandlerType BasePacket::getPacketType()
{
    return packetType;
}

#endif // BASEPACKET_H

#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include <QtGlobal>

#include "common/enums/EnumHandlerType.h"
#include "core/storage/innerPackets/BasePacket.h"

class BaseHandler {

    protected:

        static EnumHandlerType handlerType;

    public:

        BaseHandler() {};

        virtual void handle(BasePacket innerPacket) {};

        static EnumHandlerType getHandlerType();
};

inline EnumHandlerType BaseHandler::getHandlerType()
{
    return handlerType;
}

#endif // BASEHANDLER_H

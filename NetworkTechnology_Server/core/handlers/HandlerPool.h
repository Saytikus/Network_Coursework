#ifndef HANDLERPOOL_H
#define HANDLERPOOL_H

#include <QObject>
#include "BaseHandler.h"
#include <QMap>

class HandlerPool : public QObject {

    Q_OBJECT

    private:

        QMap<EnumHandlerType, BaseHandler> handlers;

    public:
        explicit HandlerPool(QObject *parent = nullptr);

        BaseHandler getHandler(const EnumHandlerType handlerType);

    signals:

};

#endif // HANDLERPOOL_H

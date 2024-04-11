#ifndef SERIALIZERPOOL_H
#define SERIALIZERPOOL_H

#include <QObject>
#include "BaseSerializer.h"
#include <QMap>

class SerializerPool : public QObject {

    Q_OBJECT

    private:

        QMap<EnumHandlerType, BaseSerializer> serializers;

    public:
        explicit SerializerPool(QObject *parent = nullptr);

        BaseSerializer getSerializer(const EnumHandlerType commandType);

    signals:

};

#endif // SERIALIZERPOOL_H

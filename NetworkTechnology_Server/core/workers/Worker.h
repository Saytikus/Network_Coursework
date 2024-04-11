#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include "core/serializers/SerializerPool.h"
#include "core/handlers/HandlerPool.h"

class Worker : public QObject {

    Q_OBJECT

    private:

        quint32 id;

        SerializerPool serializerPool;
        HandlerPool handlerPool;

    public:
        explicit Worker(const quint32 initId, QObject *parent = nullptr);


        quint32 getId() const;

    public slots:

        void doWork(QByteArray packet);


    signals:

};

#endif // WORKER_H

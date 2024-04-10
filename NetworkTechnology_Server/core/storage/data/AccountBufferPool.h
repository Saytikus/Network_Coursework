#ifndef ACCOUNTBUFFERPOOL_H
#define ACCOUNTBUFFERPOOL_H

#include <QObject>
#include <QList>
#include <QMutex>

#include "AccountBuffer.h"

class AccountBufferPool : public QObject {

    Q_OBJECT

    private:
        qint32 lastAccountBufferId;
        QList<AccountBuffer*> accountBuffers;

        QMutex mutex;

    private slots:
        void registerAccountBuffer(const QHostAddress address, const quint16 port);

        void writeSendBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);
        void writeReadBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);

        void clearSendBuffer(const quint32 accountBufferId);
        void clearReadBuffer(const quint32 accountBufferId);

        void deleteAccountBuffer(const quint32 accountBufferId);

    public:
        explicit AccountBufferPool(QObject *parent = nullptr);
        ~AccountBufferPool();

    public slots:

    signals:
        void ReadBufferChanged(const QBuffer* read_buffer, const QString buffer_id);
        void SendBufferChanged(const QBuffer* send_buffer, const QString buffer_id);

};

#endif // ACCOUNTBUFFERPOOL_H

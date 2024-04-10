#ifndef ACCOUNTBUFFERPOOL_H
#define ACCOUNTBUFFERPOOL_H

#include <QObject>
#include <QList>
#include <QMutex>
#include <QTcpServer>

#include "AccountBuffer.h"

class AccountBufferPool : public QObject {

    Q_OBJECT

    private:
        quint32 lastAccountBufferId;
        QList<AccountBuffer*> accountBuffers;

        QMutex mutex;

    private slots:
        void writeSendBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);
        void writeReadBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);

        void clearSendBuffer(const quint32 accountBufferId);
        void clearReadBuffer(const quint32 accountBufferId);

        void deleteAccountBuffer(const quint32 accountBufferId);

    public:
        explicit AccountBufferPool(QObject *parent = nullptr);
        ~AccountBufferPool();

    public slots:
        void registerAccountBuffer(const QHostAddress address, const quint16 port, const QTcpSocket* pendingSocket);

    signals:

        void accountBufferRegistered(const NetworkAddressData networkData, const QTcpSocket* pendingSocket);
        void accountBufferAlreadyExists(const QTcpSocket* pendingSocket);

        void readBufferChanged(const QByteArray newData, const quint32 qint32);
        void sendBufferChanged(const QByteArray newData, const quint32 qint32);

};

#endif // ACCOUNTBUFFERPOOL_H

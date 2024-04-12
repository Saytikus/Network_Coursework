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

        // Синглтон
        static AccountBufferPool *instance;

        static quint32 lastAccountBufferId;
        static QList<AccountBuffer*> accountBuffers;

        static bool hasReadPacket;
        static bool hasSendPacket;

        static QMutex mutex;


    private:
        static void calculateHasReadPacket();
        static void calculateHasSendPacket();

    private slots:

        static void clearSendBuffer(const quint32 accountBufferId);
        static void clearReadBuffer(const quint32 accountBufferId);

        static void deleteAccountBuffer(const quint32 accountBufferId);

    public:
        explicit AccountBufferPool(QObject *parent = nullptr);
        ~AccountBufferPool();

        // Синглтон
        static AccountBufferPool* INSTANCE()
        {

            if(!instance) {

                AccountBufferPool::mutex.lock();

                if(!instance) {
                    instance = new AccountBufferPool();
                }

                AccountBufferPool::mutex.unlock();
            }

            return instance;
        }

        static bool getHasReadPacket();

        static bool getHasSendPacket();

public slots:
        static void registerAccountBuffer(QHostAddress address, quint16 port, QTcpSocket* pendingSocket);

        static void writeSendBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);
        static void writeReadBuffer(const quint32 accountBufferId, const QByteArray data, const qint32 size);

        static QByteArray takeSendPacket();
        static QByteArray takeReadPacket();

    signals:

        void accountBufferRegistered(const NetworkAddressData networkData, const QTcpSocket* pendingSocket);
        void accountBufferAlreadyExists(const QTcpSocket* pendingSocket);

};

#endif // ACCOUNTBUFFERPOOL_H

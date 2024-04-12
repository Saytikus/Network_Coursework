#ifndef ACCOUNTBUFFER_H
#define ACCOUNTBUFFER_H

#include <QObject>
#include <QtGlobal>
#include <QBuffer>

#include "network/NetworkAddressData.h"

class AccountBuffer : public QObject {

    Q_OBJECT

    private:

        quint32 id;

        NetworkAddressData networkData;

        // Да, это плохо
        QList<QByteArray> sendBuffer;
        QList<QByteArray> readBuffer;

        bool hasReadData;
        bool hasSendData;

    public:
        explicit AccountBuffer(const quint32 initId, const NetworkAddressData initNetworkData, QObject *parent = nullptr);


        quint32 getId() const;

        NetworkAddressData getNetworkData() const;
        void setNetworkData(const NetworkAddressData newNetworkData);

        void writeSendBuffer(const QByteArray data, const qint32 size);

        void writeReadBuffer(const QByteArray data, const qint32 size);

        QList<QByteArray> getSendBuffer() const;

        QList<QByteArray> getReadBuffer() const;

        void clearSendBuffer();

        void clearReadBuffer();

        QByteArray takeSendData();

        QByteArray takeReadData();

        bool getHasReadData() const;

        bool getHasSendData() const;

signals:

};

#endif // ACCOUNTBUFFER_H

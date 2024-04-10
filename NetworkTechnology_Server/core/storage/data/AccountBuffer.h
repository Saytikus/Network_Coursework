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

        QBuffer sendBuffer;
        QBuffer readBuffer;

    public:
        explicit AccountBuffer(const quint32 initId, const NetworkAddressData initNetworkData, QByteArray *initSendBuffer, QByteArray *initReadBuffer, QObject *parent = nullptr);


        quint32 getId() const;

        NetworkAddressData getNetworkData() const;
        void setNetworkData(const NetworkAddressData newNetworkData);

        void writeSendBuffer(const QByteArray data, const qint32 size);

        void writeReadBuffer(const QByteArray data, const qint32 size);

        QByteArray getSendBuffer() const;

        QByteArray getReadBuffer() const;

        void clearSendBuffer();

        void clearReadBuffer();

    signals:

};

#endif // ACCOUNTBUFFER_H

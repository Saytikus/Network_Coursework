#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QHostAddress>
#include <QtGlobal>
#include <QTcpSocket>

#include "ApplicationServer.h"

class NetworkWorker : public QObject {

    Q_OBJECT

    private:

        ApplicationServer *server;

    public:
        explicit NetworkWorker(QObject *parent = nullptr);
        explicit NetworkWorker(ApplicationServer *server, QObject *parent = nullptr);

        void setServer(ApplicationServer *server);


    public slots:
        void sendMessage(const QByteArray message, NetworkAddressData networkAddress);

        void addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket);

        void rejectPendingConnection(const QTcpSocket* pendingSocket);

    signals:

        /**
         * @brief messageReceived - оповещение о получении сообщения
         * @param message - сообщение
         */
        void messageReceived(QByteArray message);

        /**
         * @brief requestRegisterClient - оповещение о запросе регистрации соединения клиента
         * @param addr - ip-адрес клиента
         * @param port - порт клиента
         * @param pendingSocket - сокет клиента
         */
        void requestRegisterConnection(const QHostAddress addr, const quint16 port, const QTcpSocket* pendingSocket);

};

#endif // NETWORKWORKER_H

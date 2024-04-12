#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QObject>
#include <QHostAddress>
#include <QtGlobal>
#include <QTcpSocket>
#include <QMutex>

#include "ApplicationServer.h"

class NetworkWorker : public QObject {

    Q_OBJECT

    private:

        ApplicationServer *server;

        QMutex mutex;

    public:
        explicit NetworkWorker(QObject *parent = nullptr) = delete;
        explicit NetworkWorker(ApplicationServer *server, QObject *parent = nullptr);
        ~NetworkWorker();

        void setServer(ApplicationServer *server);


    public slots:
        void sendMessage(const QByteArray message, NetworkAddressData networkAddress);

        void addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket);

        void rejectPendingConnection(const QTcpSocket* pendingSocket);

    signals:

        void finished();

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
        void requestRegisterConnection(QHostAddress addr, quint16 port, QTcpSocket* pendingSocket);

};

#endif // NETWORKWORKER_H

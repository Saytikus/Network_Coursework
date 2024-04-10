#ifndef APPLICATIONSERVER_H
#define APPLICATIONSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtGlobal>
#include <QHostAddress>
#include <QMap>

#include "NetworkAddressData.h"

/**
 * @brief The ApplicationServer class - класс-сервер приложения. Работает на протоколе TCP
 */
class ApplicationServer : public QTcpServer {

    Q_OBJECT

    private:

        /**
         * @brief addr - ip адрес, который сервер прослушивает
         */
        QHostAddress addr;

        /**
         * @brief port - порт, который сервер прослушивает
         */
        quint16 port;

        /**
         * @brief incomingConnectionSocket - актуальный на момент соединения с сервером сокет клиента
         */
        QTcpSocket *incomingConnectionSocket;

        /**
         * @brief connectedClients - словарь сетевых данных клиента и сокета клиента
         */
        QMap<NetworkAddressData, QTcpSocket*> connectedClients;

    private slots:

        /**
         * @brief onClientDisconnected - слот действий при отключении клиента
         */
        void onClientDisconnected();

    public:

        /**
         * @brief ApplicationServer - конструктор по умолчанию
         */
        ApplicationServer() {};

        ~ApplicationServer();

        /**
         * @brief init - метод инициализации сервера
         * @param initAddress - ip адрес
         * @param initPort - порт
         */
        void init(const QHostAddress initAddress, const quint16 initPort);

        /**
         * @brief start - метод запуска сервера
         * @return bool-значение результата запуска сервера
         */
        bool start();

    public slots:

        /**
         * @brief send - слот отправления сообщения на заданные сетевые данные
         * @param message - сообщение
         * @param networkAddress - сетевые данные
         */
        void send(const QByteArray message, NetworkAddressData networkAddress);

        /**
         * @brief read - слот чтения данных прочитанных сервером
         */
        void read();

        /**
         * @brief incomingConnection - слот принятия входящего соединения
         * @param socketDescriptor - идентификационный номер сокета
         */
        void incomingConnection(qintptr socketDescriptor) override;

        /**
         * @brief addPendingConnection - слот подтверждения входящего соединения
         * @param networkData - сетевые данные
         * @param pendingSocket - сокет запрашивающий подключение
         */
        void addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket);

        /**
         * @brief rejectPendingConnection - слот отклонения входящего соединения
         * @param pendingSocket - сокет запрашивающий подключение
         */
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

#endif // APPLICATIONSERVER_H

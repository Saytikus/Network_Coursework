#include "ApplicationServer.h"



/**
 * @brief init - метод инициализации сервера
 * @param initAddress - ip адрес
 * @param initPort - порт
 */
void ApplicationServer::init(const QHostAddress initAddress, const quint16 initPort) {

    // Инициализируем ресурсы и выделяем память под сокет
    this->addr = initAddress;
    this->port = initPort;
    this->incomingConnectionSocket = new QTcpSocket();
}

ApplicationServer::~ApplicationServer() {

    qDeleteAll(this->connectedClients);

    delete this->incomingConnectionSocket;

}


/**
 * @brief start - метод запуска сервера
 * @return bool-значение результата запуска сервера
 */
bool ApplicationServer::start() {

    // Пробуем начать слушать наш адрес порт
    bool result = this->listen(this->addr, this->port);

    // Выводим лог о результате попытки начать слушать адрес порт
    if(result) {
        qDebug() << "Сервер успешно запущен [" + this->addr.toString() + ":" + QString::number(this->port) + "]";
    }
    else {
        qDebug() << "Ошибка запуска сервера [" + this->addr.toString() + ":" + QString::number(this->port) + "]";
    }

    return result;
}

/**
 * @brief send - слот отправления сообщения на заданные сетевые данные
 * @param message - сообщение
 * @param networkAddress - сетевые данные
 */
void ApplicationServer::send(const QByteArray message, NetworkAddressData networkAddress) {

    // Берем сокет, в который нам нужно записать сообщение, по сетевым данным
    QTcpSocket *socket = this->connectedClients.value(networkAddress);

    // Записываем сообщение в сокет
    socket->write(message);
}

/**
 * @brief read - слот чтения данных прочитанных сервером
 */
void ApplicationServer::read() {

    // Берем сокет, с которого пришло сообщение
    QTcpSocket *socket = (QTcpSocket*)sender();

    // Читаем сокет
    QByteArray message = socket->readAll();

    // Логгируем чтение
    qDebug() << "Прочитали сообщение: " + QString(message);

    // Оповещаем о том, что мы прочитали
    emit messageReceived(message);

}

/**
 * @brief incomingConnection - слот принятия входящего соединения
 * @param socketDescriptor - идентификационный номер сокета
 */
void ApplicationServer::incomingConnection(qintptr socketDescriptor) {

    // Инициализируем новый сокет
    QTcpSocket *newSocket = new QTcpSocket;
    newSocket->setSocketDescriptor(socketDescriptor);

    // Запоминаем новый сокет
    this->incomingConnectionSocket = newSocket;

    // Отправляем запрос на регистрацию нового соединения
    emit requestRegisterConnection(newSocket->peerAddress(), newSocket->peerPort(), newSocket);

}

/**
 * @brief addPendingConnection - слот подтверждения входящего соединения
 * @param networkData - сетевые данные
 * @param pendingSocket - сокет запрашивающий подключение
 */
void ApplicationServer::addPendingConnection(const NetworkAddressData networkData, const QTcpSocket* pendingSocket) {

    // Проверка на наличие указателя
    if(this->incomingConnectionSocket == nullptr) {
        return;
    }

    // Подключаем сигналы сокета к своим слотам
    QObject::connect(this->incomingConnectionSocket, &QTcpSocket::readyRead, this, &ApplicationServer::read);
    QObject::connect(this->incomingConnectionSocket, &QTcpSocket::disconnected, this, &ApplicationServer::onClientDisconnected);

    // Логгируем действие
    qDebug() << "Клиент успешно подлючился! Данные клиента [" + this->incomingConnectionSocket->peerAddress().toString() + QString::number(this->incomingConnectionSocket->peerPort()) + "]";

    this->incomingConnectionSocket = nullptr;
}

/**
 * @brief rejectPendingConnection - слот отклонения входящего соединения
 * @param pendingSocket - сокет запрашивающий подключение
 */
void ApplicationServer::rejectPendingConnection(const QTcpSocket* pendingSocket) {

    // Проверка на наличие указателя
    if(this->incomingConnectionSocket == nullptr) {
        return;
    }

    // Логгируем действие
    qDebug() << "Подключение отклонено! Данные клиента [" + pendingSocket->peerAddress().toString() + QString::number(pendingSocket->peerPort()) + "]";

    // Очищаем память от сокета
    delete pendingSocket;
    this->incomingConnectionSocket = nullptr;
}

/**
 * @brief onClientDisconnected - слот действий при отключении клиента
 */
void ApplicationServer::onClientDisconnected() {

    // Берем необходимый сокет
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());

    // Удаляем его из нашего списка подключенных клиентов
    //NetworkAddressData netData = this->connectedClients.key(socket);
    this->connectedClients.remove(this->connectedClients.key(socket));

    // Очищаем память от сокета
    socket->deleteLater();
}

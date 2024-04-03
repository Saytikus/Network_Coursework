#include "ui/MainWindow.h"

#include <QApplication>

#include "network/ApplicationServer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // Инициализируем сервер
    ApplicationServer server;
    server.init(QHostAddress::Any, 51353);

    // Запускаем сервер
    server.start();

    MainWindow w;
    w.show();
    return a.exec();
}

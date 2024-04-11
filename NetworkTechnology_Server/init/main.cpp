#include "ui/MainWindow.h"

#include <QApplication>
#include <QThread>

#include "core/Core.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread::currentThread()->setObjectName("GUI Thread");

    // Инициализируем ядро программы
    Core core;

    // Инициализируем сетевой модуль программы
    core.initNetwork();

    MainWindow w;
    w.show();
    return a.exec();
}

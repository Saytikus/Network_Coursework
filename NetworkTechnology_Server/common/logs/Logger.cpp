#include "Logger.h"

#include <QDateTime>
#include <QDebug>
#include <QThread>


Logger* Logger::instance = 0;

QMutex Logger::mutex;

qint32 Logger::lastLogId = 0;

QList<LogRecord> Logger::logRecords = QList<LogRecord>();



Logger::Logger(QObject *parent) : QObject{parent} {
    //NO-OP
}

Logger::~Logger() {

    if(!instance) {

    }

    delete Logger::instance;

}

LogRecord Logger::recordLog(QString className, QString data) {

    QDateTime currentDateTime = QDateTime::currentDateTime();

    QString logData;

    logData.append("Время: {" + currentDateTime.toString("hh:mm:ss dd.MM.yyyy") + "}")
           .append(" Класс: {" + className + "}")
           .append(" Поток: {" + QThread::currentThread()->objectName() + "}")
           .append(" | " + data);


    Logger::mutex.lock();

    LogRecord record(++lastLogId, logData);

    Logger::logRecords.append(record);

    qDebug() << logData;

    emit instance->logRecorded(record);

    Logger::mutex.unlock();

    return record;
}

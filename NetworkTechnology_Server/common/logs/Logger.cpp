#include "Logger.h"

#include <QDateTime>
#include <QDebug>

Logger* Logger::instance = 0;

qint32 Logger::lastLogId = 0;

QList<LogRecord> Logger::logRecords = QList<LogRecord>();



Logger::~Logger() {

    if(!instance) {

    }

    delete Logger::instance;

}

LogRecord Logger::recordLog(QString className, QString data) {

    QDateTime currentDateTime = QDateTime::currentDateTime();


    QString logData;

    logData.append("Время: {" + currentDateTime.toString("hh:mm:ss dd.MM.yyyy") + "}")
           .append("Класс: {" + className + "}")
           .append(" " + data + '\n');


    LogRecord record(++lastLogId, logData);

    Logger::logRecords.append(record);

    qDebug() << logData;

    emit instance->logRecorded(record);


    return record;
}

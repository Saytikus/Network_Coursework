#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QtGlobal>
#include <QList>
#include <QMutex>

#include "LogRecord.h"

class Logger : public QObject {

    Q_OBJECT

    private:

        // Синглтон
        static Logger *instance;

        static QMutex mutex;

        static qint32 lastLogId;

        static QList<LogRecord> logRecords;


    private:

        Logger(QObject *parent = nullptr);
        Logger(const Logger& other) = delete;
        Logger& operator=(const Logger& other) = delete;

        ~Logger();

    public:

        // Синглтон
        static Logger* INSTANCE()
        {

            if(!instance) {

                Logger::mutex.lock();

                if(!instance) {
                    instance = new Logger();
                }

                Logger::mutex.unlock();
            }

            return instance;
        }



        static LogRecord recordLog(QString className, QString data);


    signals:
         void logRecorded(const LogRecord record);
};

#endif // LOGGER_H

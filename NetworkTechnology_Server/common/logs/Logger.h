#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QtGlobal>
#include <QList>

#include "LogRecord.h"

class Logger : public QObject {

    Q_OBJECT

    private:

       // Синглтон
        static Logger *instance;

        static qint32 lastLogId;

        static QList<LogRecord> logRecords;


    private:

        Logger(){}
        Logger(const Logger& other) = delete;
        Logger& operator=(const Logger& other) = delete;

        ~Logger();

    public:

       // Синглтон
        static Logger* INSTANCE()
        {
            if(!instance) {
                instance = new Logger();
            }

            return instance;
        }



        static LogRecord recordLog(QString className, QString data);


    signals:
         void logRecorded(const LogRecord record);
};

#endif // LOGGER_H

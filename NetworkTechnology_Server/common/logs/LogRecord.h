#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <QtGlobal>
#include <QString>

class LogRecord {

    private:

        qint32 id;

        QString data;

    public:
        LogRecord() = delete;
        LogRecord(const qint32 initId, const QString initData);
        qint32 getId() const;
        QString getData() const;
        void setData(const QString newData);
};

#endif // LOGRECORD_H

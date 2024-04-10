#include "LogRecord.h"


LogRecord::LogRecord(const qint32 initId, const QString initData) {
    this->id = initId;
    this->data = initData;
}

qint32 LogRecord::getId() const
{
    return id;
}

QString LogRecord::getData() const
{
    return data;
}

void LogRecord::setData(const QString newData)
{
    data = newData;
}

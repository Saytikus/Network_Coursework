#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QObject>

#include <QString>
#include <QtXml/QDomElement>
#include "core/storage/data/Account.h"
#include "Database.h"

class DatabaseReader : public QObject {

    Q_OBJECT

    public:
        explicit DatabaseReader(QObject *parent = nullptr);

        static Database readDatabaseFile(QString path);

        static Account readAccount(QDomElement xmlDomElement);

    signals:

};

#endif // DATABASEREADER_H

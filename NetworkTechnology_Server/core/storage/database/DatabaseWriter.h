#ifndef DATABASEWRITER_H
#define DATABASEWRITER_H

#include <QObject>

#include <QString>
#include <QtXml/QDomElement>
#include "core/storage/data/Account.h"
#include "Database.h"
#include <QFile>
#include <QMap>

class DatabaseWriter : public QObject {

    Q_OBJECT

    public:
        explicit DatabaseWriter(QObject *parent = nullptr);


        static void writeDatabase(QString path, Database database);


        static void writeDatabaseAccounts(QString path, QMap<quint32, Account> accounts);

        /**
         * @brief writeToXMLFile - функция непосредственной записи в файл
         * @param file - файл открываемый для записи
         * @param document - данные, которое нужно записать
         * @param codec - кодировка
         **/
        static bool writeToXMLFile(QFile* file, QDomDocument document, QString codec = "UTF-8");

    signals:

};

#endif // DATABASEWRITER_H

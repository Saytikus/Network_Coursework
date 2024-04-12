#include "DatabaseWriter.h"

#include <QTextStream>
#include <QTextCodec>

#include "common/logs/Logger.h"
#include "XMLHelper.h"
#include "core/storage/data/Account.h"
#include "XMLElementWriter.h"


DatabaseWriter::DatabaseWriter(QObject *parent)
    : QObject{parent}
{

}

void DatabaseWriter::writeDatabase(QString path, Database database) {

    DatabaseWriter::writeDatabaseAccounts(path, database.getAccounts());

}

void DatabaseWriter::writeDatabaseAccounts(QString path, QMap<quint32, Account> accounts) {

    QFile accountsFile(path + "Events.xml");
    accountsFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument accountsDoc;
    XMLHelper::writeXMLHeader(&accountsDoc);

    QDomElement accountsElement = XMLHelper::writeXMLStructTree(&accountsDoc, "Accounts");

    for (Account account : accounts.values()) {
        QDomElement eventElement = accountsDoc.createElement("Account");

        XMLElementWriter::writeUint(accountsDoc, eventElement , "id", account.getId());

        XMLElementWriter::writeText(accountsDoc, eventElement , "password", account.getPassword());
        XMLElementWriter::writeText(accountsDoc, eventElement , "password", account.getPassword());

        XMLElementWriter::writeTexts(accountsDoc, eventElement , "data", account.getData());

        accountsElement.appendChild(eventElement);
    }

    DatabaseWriter::writeToXMLFile(&accountsFile, accountsDoc, "UTF-8");

    accountsFile.close();

}

bool DatabaseWriter::writeToXMLFile(QFile* file, QDomDocument document, QString codec) {
    if (file->isOpen()) {
        QTextStream writer(file);
        writer.setCodec(QTextCodec::codecForName(codec.toStdString().data()));
        document.save(writer, 4);
        Logger::recordLog("DatabaseWriter", "Успешная запись в файл " + file->fileName());
        return true;
    } else {
        Logger::recordLog("DatabaseWriter", "Не удалось записать в файл " + file->fileName() + " Ошибка: " + file->errorString());
        return false;
    }
}

#include "DatabaseReader.h"

#include <QMap>
#include <QFile>

#include "common/const/FilePathConstants.h"
#include "common/logs/Logger.h"
#include "XMLHelper.h"
#include "core/storage/data/Account.h"
#include "XMLElementReader.h"

DatabaseReader::DatabaseReader(QObject *parent)
    : QObject{parent}
{

}

Database DatabaseReader::readDatabaseFile(QString path) {

    //QString pathToStockDatabase = "../SecurityHelper/rss/StockDatabase/";

    if (!XMLHelper::checkFile(path)) {

        Logger::recordLog("DatabaseReader", "Файл базы данных не найден, создаю чистый файл базы данных");


        /// DEBUG

        QFile emptyDatabaseFile(FilePathConstants::getDatabasePath() + FilePathConstants::getDatabaseFileName());

        emptyDatabaseFile.open(QFile::ReadOnly | QFile::Text);

        if(!emptyDatabaseFile.isOpen()) {
            Logger::recordLog("DatabaseReader", "Не удалось создать чистый файл базы данных");
            return Database();
        }

        QDomDocument databaseDoc;
        XMLHelper::writeXMLHeader(&databaseDoc);

        QDomElement databaseElement = XMLHelper::writeXMLStructTree(&databaseDoc, "Accounts");


        //return XMLHelper::readDatabase(pathToStockDatabase);

        /// DEBUG
    }

    QMap<quint32, Account> accounts;

    QFile databaseFile(path + "Events.xml");
    databaseFile.open(QFile::ReadOnly | QFile::Text);
    QDomDocument accountsDoc;
    accountsDoc.setContent(&databaseFile);
    QDomElement accountsDatabaseDomElement = XMLHelper::readSingleNode(accountsDoc.documentElement(), "Database");
    QDomElement databaseDomElement = XMLHelper::readSingleNode(accountsDatabaseDomElement, "Accounts");
    QList<QDomElement> accountListDomElements = XMLHelper::readMultiNode(databaseDomElement, "Account");

    for (QDomElement accountDomElement : accountListDomElements) {
        Account account = DatabaseReader::readAccount(accountDomElement);
        accounts.insert(account.getId(), account);
    }

    databaseFile.close();

    return Database(accounts);
}

Account DatabaseReader::readAccount(QDomElement xmlDomElement) {

    quint32 accountId = XMLElementReader::readUint(xmlDomElement, "id");

    QString accountLogin = XMLElementReader::readText(xmlDomElement, "password");;
    QString accountPassword = XMLElementReader::readText(xmlDomElement, "login");;

    QStringList accountData = XMLElementReader::readTexts(xmlDomElement, "data");

    return Account(accountId, accountLogin, accountPassword, accountData);
}

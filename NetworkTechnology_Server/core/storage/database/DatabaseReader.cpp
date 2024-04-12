#include "DatabaseReader.h"

#include <QMap>
#include <QFile>
#include <QDir>

#include "common/logs/Logger.h"
#include "XMLHelper.h"
#include "core/storage/data/Account.h"
#include "XMLElementReader.h"
#include "DatabaseFileCreator.h"


DatabaseReader::DatabaseReader(QObject *parent)
    : QObject{parent}
{

}

Database DatabaseReader::readDatabaseFile(QString path) {


    if (!XMLHelper::checkFile(path)) {

        Logger::recordLog("DatabaseReader", "Файл базы данных не найден, запрашиваю создание чистого файла базы данных");

        DatabaseFileCreator::createDatabaseFile();

        return Database();
    }

    QMap<quint32, Account> accounts;

    QFile databaseFile(path);
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

    QString accountLogin = XMLElementReader::readText(xmlDomElement, "login");;
    QString accountPassword = XMLElementReader::readText(xmlDomElement, "password");;

    QStringList accountData = XMLElementReader::readTexts(xmlDomElement, "data");

    return Account(accountId, accountLogin, accountPassword, accountData);
}

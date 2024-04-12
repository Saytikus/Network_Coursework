#include "DatabaseFileCreator.h"

#include <QString>
#include <QDir>
#include <QFile>

#include "XMLHelper.h"
#include "DatabaseWriter.h"
#include "common/const/FilePathConstants.h"
#include "common/logs/Logger.h"

DatabaseFileCreator::DatabaseFileCreator(QObject *parent)
    : QObject{parent}
{

}

void DatabaseFileCreator::createDatabaseFile() {

    QString dirName = "database";

    if(!QDir(dirName).exists()) {
        QDir().mkdir(dirName);
    }

    QString databaseDirPath = QDir(dirName).absolutePath();

    QFile emptyDatabaseFile(FilePathConstants::getDatabasePath() + FilePathConstants::getDatabaseFileName());

    emptyDatabaseFile.open(QFile::WriteOnly | QFile::Text);

    if(!emptyDatabaseFile.isOpen()) {
        Logger::recordLog("DatabaseFileCreator", "Не удалось создать чистый файл базы данных");
        throw std::runtime_error("Не удалось создать чистый файл базы данных");
    }

    QDomDocument databaseDoc;
    XMLHelper::writeXMLHeader(&databaseDoc);

    QDomElement databaseElements = XMLHelper::writeXMLStructTree(&databaseDoc, "Accounts");

    DatabaseWriter::writeToXMLFile(&emptyDatabaseFile, databaseDoc, "UTF-8");

    Logger::recordLog("DatabaseFileCreator", "Чистый файл базы данных успешно создан! Путь: " + QDir().absoluteFilePath(emptyDatabaseFile.fileName()));

    emptyDatabaseFile.close();

}

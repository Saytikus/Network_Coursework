#include "FilePathConstants.h"


QString FilePathConstants::databasePath = "./database/";

QString FilePathConstants::databaseFileName = "database.xml";



FilePathConstants::FilePathConstants()
{

}


QString FilePathConstants::getDatabasePath()
{
    return databasePath;
}

QString FilePathConstants::getDatabaseFileName()
{
    return databaseFileName;
}

#ifndef FILEPATHCONSTANTS_H
#define FILEPATHCONSTANTS_H

#include <QString>

class FilePathConstants {

    private:

        static QString databasePath;

        static QString databaseFileName;

    public:
        FilePathConstants();

        static QString getDatabasePath();
        static QString getDatabaseFileName();
};

#endif // FILEPATHCONSTANTS_H

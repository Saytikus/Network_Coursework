#ifndef DATABASEFILECREATOR_H
#define DATABASEFILECREATOR_H

#include <QObject>

class DatabaseFileCreator : public QObject {

    Q_OBJECT

    public:
        explicit DatabaseFileCreator(QObject *parent = nullptr);

        static void createDatabaseFile();

    signals:

};

#endif // DATABASEFILECREATOR_H

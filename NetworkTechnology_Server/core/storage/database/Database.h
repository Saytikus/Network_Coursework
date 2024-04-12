#ifndef DATABASE_H
#define DATABASE_H

#include <QtGlobal>
#include <QObject>
#include <QMap>

#include "core/storage/data/Account.h"

class Database : public QObject {

    Q_OBJECT

    private:

        QMap<quint32, Account> accounts;

    public:
        Database(QObject *parent = nullptr);
        Database(QMap<quint32, Account> initAccounts, QObject *parent = nullptr);
        Database(const Database &other);

        QMap<quint32, Account> getAccounts() const;
        void setAccounts(const QMap<quint32, Account> &newAccounts);

signals:

};

#endif // DATABASE_H

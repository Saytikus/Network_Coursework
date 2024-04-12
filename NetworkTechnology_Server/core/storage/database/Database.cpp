#include "Database.h"



Database::Database(QObject *parent) : QObject{parent} {
    // NO-OP
}

Database::Database(QMap<quint32, Account> initAccounts, QObject *parent) : QObject{parent} {
    this->accounts = initAccounts;
}

Database::Database(const Database &other) {
    this->accounts = other.accounts;
}

QMap<quint32, Account> Database::getAccounts() const
{
    return accounts;
}

void Database::setAccounts(const QMap<quint32, Account> &newAccounts)
{
    accounts = newAccounts;
}

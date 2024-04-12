#include "Account.h"


Account::Account(QObject *parent) : QObject{parent} {
    // NO-OP
}

Account::Account(const quint32 initId, const QString initLogin, const QString initPassword, const QStringList initData, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
    this->login = initLogin;
    this->password = initPassword;
    this->data = initData;
}

Account::Account(const Account &other) {
    this->id = other.id;
    this->login = other.login;
    this->password = other.password;
    this->data = other.data;
}

Account& Account::operator=(const Account &other) {
    if(&other == this) {
        return *this;
    }

    QObject::setParent(other.parent());

    this->id = other.id;
    this->login = other.login;
    this->password = other.password;
    this->data = other.data;

    return *this;
}




void Account::appendDataString(const QString dataString) {
    this->data.append(dataString);
}

QString Account::takeDataString(const QString dataString) {
    return this->takeDataString(this->data.indexOf(dataString));
}

QString Account::takeDataString(const qint32 position) {
    return this->data.takeAt(position);
}

void Account::removeDataString(const QString dataString) {
    this->data.removeOne(dataString);
}

void Account::clearData() {
    this->data.clear();
}

QStringList Account::getData() const {
    return data;
}

void Account::setData(const QStringList newData) {
    this->data = newData;
}

quint32 Account::getId() const {
    return id;
}

QString Account::getLogin() const {
    return login;
}

QString Account::getPassword() const {
    return password;
}

void Account::setPassword(const QString newPassword) {
    password = newPassword;
}

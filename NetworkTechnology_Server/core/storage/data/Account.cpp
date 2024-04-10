#include "Account.h"



Account::Account(const quint32 initId, const quint32 initBufferId, const QString initLogin, const QString initPassword, const QStringList initData, QObject *parent)
    : QObject{parent}
{
    this->id = initId;
    this->bufferId = initBufferId;
    this->login = initLogin;
    this->password = initPassword;
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

quint32 Account::getId() const {
    return id;
}

quint32 Account::getBufferId() const {
    return bufferId;
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

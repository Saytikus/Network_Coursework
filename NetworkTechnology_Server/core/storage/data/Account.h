#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>
#include <QtGlobal>


class Account : public QObject {

    Q_OBJECT

    private:

        quint32 id;

        quint32 bufferId;

        QString login;

        QString password;

        QStringList data;

    public:
        explicit Account(const quint32 initId, const quint32 initBufferId, const QString initLogin, const QString initPassword, const QStringList initData, QObject *parent = nullptr);

        quint32 getId() const;

        quint32 getBufferId() const;

        QString getLogin() const;

        QString getPassword() const;
        void setPassword(const QString newPassword);

        QStringList getData() const;

        void appendDataString(const QString dataString);

        QString takeDataString(const QString dataString);

        QString takeDataString(const qint32 position);

        void removeDataString(const QString dataString);

        void clearData();



    signals:

};

#endif // ACCOUNT_H

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>
#include <QtGlobal>


class Account : public QObject {

    Q_OBJECT

    private:

        quint32 id;

        QString login;

        QString password;

        QStringList data;

    public:
        Account(QObject *parent = nullptr);

        Account(const quint32 initId, const QString initLogin, const QString initPassword, const QStringList initData, QObject *parent = nullptr);

        Account(const Account &other);

        Account& operator=(const Account &other);

        quint32 getId() const;

        QString getLogin() const;

        QString getPassword() const;
        void setPassword(const QString newPassword);

        QStringList getData() const;
        void setData(const QStringList newData);


        void appendDataString(const QString dataString);

        QString takeDataString(const QString dataString);

        QString takeDataString(const qint32 position);

        void removeDataString(const QString dataString);

        void clearData();



    signals:

};

#endif // ACCOUNT_H

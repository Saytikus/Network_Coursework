#ifndef ACCOUNTREGISTRATIONPACKET_H
#define ACCOUNTREGISTRATIONPACKET_H

#include <QString>

#include "BasePacket.h"

class AccountRegistrationPacket : public BasePacket {

    private:

        QString login;

        QString password;

    public:

        AccountRegistrationPacket(const QString login, const QString password);

        QString getLogin() const;
        void setLogin(const QString newLogin);
        QString getPassword() const;
        void setPassword(const QString newPassword);
};


EnumHandlerType AccountRegistrationPacket::BasePacket::packetType = EnumHandlerType::AccountRegistration;


AccountRegistrationPacket::AccountRegistrationPacket(const QString login, const QString password) {

    this->login = login;
    this->password = password;

}

inline QString AccountRegistrationPacket::getPassword() const
{
    return password;
}

inline void AccountRegistrationPacket::setPassword(const QString newPassword)
{
    password = newPassword;
}

inline QString AccountRegistrationPacket::getLogin() const
{
    return login;
}

inline void AccountRegistrationPacket::setLogin(const QString newLogin)
{
    login = newLogin;
}

#endif // ACCOUNTREGISTRATIONPACKET_H

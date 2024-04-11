#ifndef ACCOUNTREGISTRATIONHANDLER_H
#define ACCOUNTREGISTRATIONHANDLER_H

#include <QObject>
#include "BaseHandler.h"

#include <QString>

class AccountRegistrationHandler : public QObject, public BaseHandler {

    Q_OBJECT

    private:

    public:
        explicit AccountRegistrationHandler(QObject *parent = nullptr);

        virtual void handle(BasePacket packet) override;

signals:

};

#endif // ACCOUNTREGISTRATIONHANDLER_H

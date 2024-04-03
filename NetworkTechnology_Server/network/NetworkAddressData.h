#ifndef NETWORKADDRESSDATA_H
#define NETWORKADDRESSDATA_H

#include <QtGlobal>
#include <QHostAddress>


class NetworkAddressData {

    private:

        QHostAddress address;

        quint16 port;

        quint32 id;

    public:

        NetworkAddressData() {};

        NetworkAddressData(const quint32 initId, const QHostAddress initAddress, const quint16 initPort) : address(initAddress), port(initPort), id(initId) {}

        NetworkAddressData(const NetworkAddressData &other) {
            this->address = other.address;
            this->port = other.port;
            this->id = other.id;
        }

        bool operator<(const NetworkAddressData other) const {
            return     this->address.toIPv4Address() < other.address.toIPv4Address()
                    && this->port < other.port
                    && this->id < other.id;
        }

        void setAddress(const QHostAddress newAddress) {

            this->address = newAddress;
        }

        void setPort(const quint16 newPort) {
            this->port = newPort;
        }

        void setId(const quint32 newId) {
            this->id = newId;
        }

        QHostAddress getAddress() { return this->address; }

        quint16 getPort() { return this->port; }

        quint32 getId() { return this->id; }


};

#endif // NETWORKADDRESSDATA_H

#ifndef NETWORKADDRESSDATA_H
#define NETWORKADDRESSDATA_H

#include <QtGlobal>
#include <QHostAddress>


class NetworkAddressData {

    private:

        QHostAddress address;

        quint16 port;

    public:

        NetworkAddressData() {};

        NetworkAddressData(const QHostAddress initAddress, const quint16 initPort) : address(initAddress), port(initPort) {}

        NetworkAddressData(const NetworkAddressData &other) {
            this->address = other.address;
            this->port = other.port;
        }

        NetworkAddressData& operator=(const NetworkAddressData &other) {
            if(&other == this) {
                return *this;
            }

            this->address = other.address;
            this->port = other.port;
        }

        bool operator<(const NetworkAddressData other) const {
            return     this->address.toIPv4Address() < other.address.toIPv4Address()
                    && this->port < other.port;
        }

        void setAddress(const QHostAddress newAddress) {

            this->address = newAddress;
        }

        void setPort(const quint16 newPort) {
            this->port = newPort;
        }


        QHostAddress getAddress() { return this->address; }

        quint16 getPort() { return this->port; }


};

#endif // NETWORKADDRESSDATA_H

#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &NetworkHandler::processPendingDatagrams);
}

void NetworkHandler::processPendingDatagrams()
{
    QByteArray datagram;

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString receivedData = QString::fromUtf8(datagram);

        if (receivedData.contains("pi-connection-request")) {
            emit connectionRequest(sender, senderPort);
        }
    }
}

void NetworkHandler::setConnection(QHostAddress *address, quint16 port)
{
    piDashAddress = address;

    QByteArray datagram = "pi-connection-accepted";
    udpSocket->writeDatagram(datagram, *address, port);
}

bool NetworkHandler::isConnected()
{
    if (piDashAddress) return true;
    return false;
}

#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &NetworkHandler::processPendingDatagrams);

    connect (&timer, &QTimer::timeout,
            this, &NetworkHandler::broadcastConnectionRequest);
}

void NetworkHandler::processPendingDatagrams()
{
    QByteArray datagram;

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));

        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(
            datagram.data(), datagram.size(),
            &sender, &senderPort);

        QString receivedData = QString::fromUtf8(datagram);

        if (receivedData.contains("pi-connection-accepted")) {
            emit requestAccepted(/*sender, senderPort*/);
        }
    }
}

void NetworkHandler::startBroadcasting()
{
    timer.start(1000);
}

void NetworkHandler::broadcastConnectionRequest()
{
    QByteArray datagram = "pi-connection-request";
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
}

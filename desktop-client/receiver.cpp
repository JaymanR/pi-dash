#include "receiver.h"
#include <QString>

Receiver::Receiver(QWidget *parent)
    : QWidget{parent}
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Receiver::processPendingDatagrams);
}

void Receiver::processPendingDatagrams()
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

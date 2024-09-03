#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

signals:
    void requestAccepted(/*QHostAddress sender, quint16 port*/);

public slots:
    void startBroadcasting();

private:
    QUdpSocket *udpSocket{nullptr};
    QTimer timer;

private slots:
    void broadcastConnectionRequest();
    void processPendingDatagrams();

};

#endif // NETWORKHANDLER_H

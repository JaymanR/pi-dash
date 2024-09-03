#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QUdpSocket>

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

    void setConnection(QHostAddress *address, quint16 port);
    bool isConnected();

signals:
    void connectionRequest(QHostAddress sender, quint16 port);

private:
    QUdpSocket *udpSocket{nullptr};
    QHostAddress *piDashAddress{nullptr};

private slots:
    void processPendingDatagrams();

};

#endif // NETWORKHANDLER_H

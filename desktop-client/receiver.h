#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QUdpSocket>

class Receiver : public QWidget
{
    Q_OBJECT
public:
    explicit Receiver(QWidget *parent = nullptr);

signals:
    void connectionRequest(QHostAddress sender, quint16 port);

private:
    QUdpSocket *udpSocket{nullptr};

private slots:
    void processPendingDatagrams();

};

#endif // RECEIVER_H

#ifndef TCPLINK_H
#define TCPLINK_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
class TcpLink : public QObject
{
    Q_OBJECT
public:
    explicit TcpLink(QObject *parent = nullptr);

signals:
private slots:
    void newConnectSlot();
    void readyRead_Slot();
private:
    QTcpServer *tcpserver;
    QTcpSocket *socket;
};


#endif // TCPLINK_H

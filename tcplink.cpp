#include "tcplink.h"

TcpLink::TcpLink(QObject *parent) : QObject(parent)
{
    tcpserver = new QTcpServer(this);
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(newConnectSlot()));
    tcpserver->listen(QHostAddress::Any,8899);
    socket=new QTcpSocket(this);
}

void TcpLink::newConnectSlot()
{
    socket=tcpserver->nextPendingConnection();//获取已经连接的客户端套接字
    qDebug() << "newConnectSlot执行";
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));
}
///
/// \brief TcpLink::readyRead_Slot
///接受客户端请求处理
void TcpLink::readyRead_Slot()
{
    QByteArray array = socket->readAll();
}

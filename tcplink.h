#ifndef TCPLINK_H
#define TCPLINK_H

#include "broadcastmain.h"
#include "dispatcher.h"
#include <functional>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDataStream>

class TcpLink : public QObject
{
    Q_OBJECT
public:
    static TcpLink* getTcpLink(){
        static TcpLink instance;
        return &instance;
    };
    QJsonObject UserLogin(QJsonObject &Obj);
    QJsonObject getAllFuncs(QJsonObject &obj);
    void WriteData(QJsonObject &obj);
signals:

private:
    void JsonAnalysis(QByteArray &buf);

private slots:
    void newConnectSlot();
    void readyRead_Slot();
private:
    QTcpServer *tcpserver;
    QTcpSocket *socket;
    explicit TcpLink(QObject *parent = nullptr);
};


#endif // TCPLINK_H

#include "connect/http/httpsession.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextStream>
#include <QDataStream>
#include <QJsonDocument>
#include"connect/dispatcher.h"
httpSession::httpSession(QTcpSocket *socket, QObject *parent)
    : QObject{parent} ,mysocket {socket}
{
    connect(mysocket, &QTcpSocket::readyRead, this, &httpSession::handleHttpRequest);
    connect(mysocket, &QTcpSocket::disconnected, this, &httpSession::deleteLater);
    connect(mysocket, &QTcpSocket::disconnected, this, &httpSession::socketDisconnected);

}

void httpSession::handleHttpRequest()
{
    QTextStream stream(mysocket);
    QString method;
    QString path;

    // 读取请求行
    if (mysocket->canReadLine()) {
        QString requestLine = mysocket->readLine().trimmed();
        QStringList requestParts = requestLine.split(" ");
        if (requestParts.size() >= 2) {
            method = requestParts[0];
            path = requestParts[1];
        }
    }

    // 读取请求头
    while (mysocket->canReadLine()) {
        QString headerLine = mysocket->readLine().trimmed();
        if (headerLine.isEmpty()) {
            break;
        }
    }

    // 读取请求体
    QByteArray requestBody;
    while (mysocket->bytesAvailable() > 0) {
        requestBody.append(mysocket->readAll());
    }

    qDebug() << "Request path: " << path;
    qDebug() << "Request body: " << QString(requestBody);

    // 将请求体转换为Json对象
    QJsonDocument doc = QJsonDocument::fromJson(requestBody);
    QJsonObject obj = doc.object();

    // 分发请求

    QJsonObject response = Dispatcher::getDispatcher()->Dispatch(obj.value ("required").toString (), obj);


    // 将Json对象转换为字节数组
    QJsonDocument docResponse(response);
    QByteArray data = docResponse.toJson(QJsonDocument::Compact); // 将QJsonDocument转换为QByteArray
    QString strJson(data); // 将QByteArray转换为QString

    QString a ;
    a.append("HTTP/1.1 200 OK\r\n");
    a.append("Server:nginx\r\n");
    a.append("Content-Type:application/json;charset=UTF-8\r\n");
    a.append("Connection:keep-alive\r\n");
    a.append(QString("Content-Length:%1\r\n\r\n").arg(data.size())); // 使用QByteArray::size()获取字节数
    a.append(strJson);
    qDebug()<<a;

    mysocket->write(a.toStdString().c_str());

}

void httpSession::socketDisconnected(){
    qDebug()<<"close";
}

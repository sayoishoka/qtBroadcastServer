#include "device_management.h"
#include "ui_device_management.h"

Device_Management::Device_Management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Device_Management)
{
    ui->setupUi(this);
    Dispatcher::getDispatcher()->Register("setDevVolume",std::bind(&Device_Management::setDevVolume, this,std::placeholders::_1));
}

Device_Management::~Device_Management()
{
    delete ui;
}

QJsonObject Device_Management::setDevVolume(QJsonObject &obj)
{
    QString devNo = obj.value("devNo").toString();
    QString volume = QString::number(obj.value("volume").toInt());
    QJsonObject requestjson;
    QSqlQuery query = BroadcastMain::getData_Sheet("UPDATE device SET volume = '"+volume+"' WHERE dev_no = '"+devNo+"'");
    requestjson.insert("response","reSetDevVolume");
    requestjson.insert("status",true);
    return requestjson;
}

QJsonObject Device_Management::setDevsVolume(QJsonObject &obj)
{
    QJsonArray devNo = obj.value("devNo").toArray();
    QString volume = QString::number(obj.value("volume").toInt());
    QString dev = "";
    for (int i=0;i<devNo.size();i++) {
        int de = devNo[i].toInt();
        if (i==0){
            dev += QString::number(de);
        }else{
            dev += ","+QString::number(de);
        }
    }
    QJsonObject requestjson;
    QSqlQuery query = BroadcastMain::getData_Sheet("UPDATE device SET volume = '"+volume+"' WHERE dev_no IN ("+dev+")");
    requestjson.insert("response","reSetDevsVolume");
    requestjson.insert("status",true);
    return requestjson;
}

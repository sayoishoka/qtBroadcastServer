#ifndef DEVICE_MANAGEMENT_H
#define DEVICE_MANAGEMENT_H

#include <QWidget>
#include "broadcastmain.h"
namespace Ui {
class Device_Management;
}

class Device_Management : public QWidget
{
    Q_OBJECT

public:
    static Device_Management* getDevice_Management(){
        static Device_Management instance;
        return &instance;
    };
    QJsonObject setDevVolume(QJsonObject &obj);
    QJsonObject setDevsVolume(QJsonObject &obj);
    ~Device_Management();

private:

    explicit Device_Management(QWidget *parent = nullptr);
    Ui::Device_Management *ui;
};

#endif // DEVICE_MANAGEMENT_H

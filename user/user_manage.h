#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include "broadcastmain.h"
#include <QWidget>
#include <QScrollBar>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
namespace Ui {
class User_Manage;
}

class BroadcastMain;

class User_Manage : public QWidget
{
    Q_OBJECT

public:

    ~User_Manage();

    static User_Manage* getUser_Manage(){
        static User_Manage instance;
        return &instance;
    };
signals:
    void getdata();
private:
    QTimer* timer;
    void setTable();
    void update_data();//更新表格数据
    explicit User_Manage(QWidget *parent = nullptr);
    Ui::User_Manage *ui;
};

#endif // USER_MANAGE_H

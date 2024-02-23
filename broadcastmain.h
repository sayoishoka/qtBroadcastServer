#ifndef BROADCASTMAIN_H
#define BROADCASTMAIN_H
#include "menu.h"
#include "user/userdata.h"
#include "databaseconfig.h"
#include <QWidget>

#include <QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class BroadcastMain; }
QT_END_NAMESPACE

class Menu;
class User_Manage;
class BroadcastMain : public QWidget
{
    Q_OBJECT

public:
    QList<User> userdata;

    ~BroadcastMain();

    static BroadcastMain* getBroadcastMain(){
        static BroadcastMain instance;
        return &instance;
    };

public:
    bool DataBaseLinkok;
    static QSqlQuery getData_Sheet(QString sheet);
    void databaselink();
private slots:
    void on_register_2_clicked();

    void on_return_2_clicked();

    void on_exit_clicked();

    void on_logon_clicked();


    void on_register_3_clicked();

private:
    BroadcastMain(QWidget *parent = nullptr);
    void init();
    DatabaseConfig *databaseconfig;
    Menu *menu;
    User_Manage *userman;
    Ui::BroadcastMain *ui;
};

#endif // BROADCASTMAIN_H


#ifndef BROADCASTMAIN_H
#define BROADCASTMAIN_H

#include "databaseconfig.h"
#include <QWidget>
#include <menu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BroadcastMain; }
QT_END_NAMESPACE

//class DatabaseConfig;
class BroadcastMain : public QWidget
{
    Q_OBJECT

public:


    ~BroadcastMain();

    static BroadcastMain* getBroadcastMain(){
        static BroadcastMain instance;
        return &instance;
    };

public:
    bool DataBaseLinkok;
    void databaselink();
private slots:
    void on_register_2_clicked();

    void on_return_2_clicked();

    void on_exit_clicked();

    void on_logon_clicked();


private:
    BroadcastMain(QWidget *parent = nullptr);
    void init();
    DatabaseConfig *databaseconfig;
    Menu *menu;

    Ui::BroadcastMain *ui;
};

#endif // BROADCASTMAIN_H


#include "broadcastmain.h"
#include "databaseconfig.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    BroadcastMain *w = new BroadcastMain();
    /// w : 0x111
    BroadcastMain *w = BroadcastMain::getBroadcastMain();
//            connect(a,&modifydata::refreshdata,this,&soundmanagemant::refreshTabWidgetdata);
//    if (w->DataBaseLinkok){
//        qDebug() << "数据库连接成功";
//        //QMessageBox::information(this, "提示", "数据库连接成功");
//        w->show();
//    } else {
//        QMessageBox::information(w, "提示", "数据库连接失败,请重新配置数据库");
//        database->show();
//    }

    return a.exec();
}

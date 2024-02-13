#include "broadcastmain.h"
#include "ui_broadcastmain.h"
#include "databaseconfig.h"

#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
BroadcastMain::BroadcastMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BroadcastMain)
{
    menu = new Menu();
    databaseconfig = new DatabaseConfig();
    ui->setupUi(this);
    init();
    databaselink();
    connect(databaseconfig,&DatabaseConfig::Showdbconfig,[=](){
        databaselink();
    });

}

BroadcastMain::~BroadcastMain()
{
    delete ui;
}

///
/// \brief BroadcastMain::on_register_2_clicked
/// 注册按钮的响应函数
void BroadcastMain::on_register_2_clicked()
{
    qDebug() << "打开注册";
    ui->stackedWidget->setCurrentIndex(1);
}

void BroadcastMain::on_return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
///
/// \brief BroadcastMain::on_exit_clicked
///退出按钮的响应函数
void BroadcastMain::on_exit_clicked()
{
    qApp->quit();
}
///
/// \brief BroadcastMain::on_logon_clicked
///登录按钮的响应函数
void BroadcastMain::on_logon_clicked()
{

    QString username=ui->user_name->text();
    QString userpsd=ui->user_pwd->text();
    QSqlQuery query;
    if(QString::localeAwareCompare(username,"")==0||QString::localeAwareCompare(userpsd,"")==0){
          QMessageBox::information(this, "提示", "用户名或密码为空");
    }else{
        query.exec("select * from user where user_accountnumber='" + username +"'");
        qDebug()<<query.size();
        if (query.size()==-1||query.size()==0){
            QMessageBox::information(this, "提示", "用户名或密码有误");
        }else{
            while(query.next()){
                qDebug()/*<<query.value("id").toInt()*/
                         <<query.value(0).toInt()
                        <<query.value(1).toString().toUtf8().data()
                       <<query.value(2).toString().toUtf8().data()
                      <<query.value(3).toString().toUtf8().data()
                     <<query.value(4).toString().toUtf8().data()
                    <<query.value(5).toInt();
                if (QString::localeAwareCompare(userpsd,query.value("user_password").toString())!=0){
                    QMessageBox::information(this, "提示", "用户名或密码有误");
                }else{
                    this->hide();
                    menu->show();
                }
            }
        }
    }
}
///
/// \brief BroadcastMain::init
///登录界面的ui属性设置
void BroadcastMain::init()
{
    this->setWindowTitle("登录");
    ui->user_pwd->setPlaceholderText("输入用户密码");
    ui->user_name->setPlaceholderText("输入用户名");
}
///
/// \brief BroadcastMain::databaselink
///数据库的连接配置
void BroadcastMain::databaselink()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QSettings *settings = new QSettings("D:/qtproject1/BroadcastServer/mysqlprofile.ini", QSettings::IniFormat);
//        db.setHostName("127.0.0.1");  //连接本地主机
//        db.setPort(3306);
//        db.setDatabaseName("qtserver");
//        db.setUserName("root");
//        db.setPassword("123456");
        if(settings->contains(tr("/mysql/ip"))&&settings->contains(tr("/mysql/port"))&&settings->contains(tr("/mysql/database"))
                &&settings->contains(tr("/mysql/username"))&&settings->contains(tr("/mysql/userpassword")))
        {
//            db.setHostName(settings->value( "/mysql/ip").toString());  //连接本地主机
//            db.setPort(settings->value( "/mysql/port").toInt());
//            db.setDatabaseName(settings->value( "/mysql/database").toString());
//            db.setUserName(settings->value( "/mysql/username").toString());
//            db.setPassword(settings->value( "/mysql/userpassword").toString());
        } else {
            settings->beginGroup(tr("mysql"));
            settings->setValue("ip","127.0.0.1");
            settings->setValue("port","3306");
            settings->setValue("database","qtserver");
            settings->setValue("username","root");
            settings->setValue("userpassword","123456");
            settings->endGroup();
//            db.setHostName(settings->value( "/mysql/ip").toString());  //连接本地主机
//            db.setPort(settings->value( "/mysql/port").toInt());
//            db.setDatabaseName(settings->value( "/mysql/database").toString());
//            db.setUserName(settings->value( "/mysql/username").toString());
//            db.setPassword(settings->value( "/mysql/userpassword").toString());
        }
        db.setHostName(settings->value( "/mysql/ip").toString());  //连接本地主机
        db.setPort(settings->value( "/mysql/port").toInt());
        db.setDatabaseName(settings->value( "/mysql/database").toString());
        db.setUserName(settings->value( "/mysql/username").toString());
        db.setPassword(settings->value( "/mysql/userpassword").toString());
        bool DataBaseLinkok = db.open();
        if (DataBaseLinkok){
            qDebug() << "数据库连接成功";
            this->show();
            //QMessageBox::information(this, "提示", "数据库连接成功");
        } else {
//            QMessageBox::information(this, "提示", "数据库连接失败");
            databaseconfig = DatabaseConfig::getDatabaseConfig();
            databaseconfig->show();
        }
}

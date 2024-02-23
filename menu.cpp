#include "menu.h"
#include "ui_menu.h"

#include <QDebug>
QString Menu::usena = "";
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    init();
    timerr();
    signal_slotConnection();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::UserName(QString name)
{
    Menu::usena = name;
}


void Menu::Open_Function(QTreeWidgetItem *item, int column)
{
    qDebug() << item->text(0);
    if (QString::localeAwareCompare(item->text(0),"用户管理")==0){
        ui->stackedWidget->addWidget(User_Manage::getUser_Manage());
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(User_Manage::getUser_Manage()));
    }else if (QString::localeAwareCompare(item->text(0),"主页")==0){
        ui->stackedWidget->setCurrentIndex(0);
    }else if (QString::localeAwareCompare(item->text(0),"角色管理")==0){
        ui->stackedWidget->addWidget(Role_management::getRole_management());
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(Role_management::getRole_management()));
    }else if (QString::localeAwareCompare(item->text(0),"权限管理")==0){
        ui->stackedWidget->addWidget(Rights_management::getRights_management());
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(Rights_management::getRights_management()));
    }
}

void Menu::timerr()
{
    QDateTime dateTime1 =QDateTime::currentDateTime();//获取系统时间
    ui->time->setText(dateTime1.toString("hh:mm:ss"));
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        QDateTime dateTime2 =QDateTime::currentDateTime();//获取当前系统时间
        ui->time->setText(dateTime2.toString("hh:mm:ss"));
        pMenuTest1->setTitle(Menu::usena);
    });//连接信号槽
    timer->start(1000);//1s更新一次
}

void Menu::init()
{
    ui->treeWidget->setStyleSheet(QString(""
                                               "QWidget{background-color: rgb(227, 222, 214);}"
                                               "QTreeWidget::item{height: 40;}"
                                               "QTreeWidget{background-color: rgb(227, 222, 214);"
                                               "\nfont: 17px 'Microsoft YaHei';\ncolor: rgb(0, 0, 0);}"
                                               "QTreeView::arrow{background-color:black ;}"
                                               )
                                       );
    //隐藏treeWidget的Header
    ui->treeWidget->setHeaderHidden(true);
    QHeaderView *head = ui->treeWidget->header();
    head->setSectionResizeMode(QHeaderView::ResizeToContents);
    //设置treeWidget Icon大小
        ui->treeWidget->setIconSize(QSize(30,30));

        //隐藏treeWidget水平和垂直滚动条
        ui->treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //设置treeWidget展开和隐藏动画
        ui->treeWidget->setAnimated(true);

        //默认展开所有的treeWidget项
        ui->treeWidget->expandAll();

        //设置多级菜单部件的最大宽度
        //        this->setMaximumWidth(350);

        pMenuBar = new QMenuBar;

        pMenuBar->setStyleSheet("QMenuBar{font-size:18px;height:65px;background-color:transparent;}"/*设置背景色，跟随背景色*/
                               "QMenuBar::selected{background-color:transparent;}"/*设置菜单栏选中背景色*/
                               "QMenuBar::item{widget:80px;font-size:30px;font-family:Microsoft YaHei;color:rgba(0,0,0,1);}"/*设置菜单栏字体为黑色，透明度为1（取值范围0.0-255）*/
                                );
        pMenuTest1 = new QMenu("用户名");

//        pMenuTest1->setFixedHeight(300);//这样只把菜单变大了
//        pMenuTest1->setMinimumWidth(150);//指定菜单的宽度
        pMenuTest1->setStyleSheet("QMenu{background:rgba(255,255,255,1);border:none;font-size:16px;}"
                                  "QMenu::item{padding:11px 32px;color:rgba(51,51,51,1);font-size:16px;}"
                                  "QMenu::item:hover{background-color:#409CE1;}"
                                  "QMenu::item:selected{background-color:#409CE1;}");
        pActionTest1 = new QAction("个人信息修改");
        pActionTest2 = new QAction("切换账号");
        pActionTest3 = new QAction("登出");
        list1.append(pActionTest1);
        list1.append(pActionTest2);
        list1.append(pActionTest3);
        pMenuTest1->addActions(list1);
        pMenuBar->addMenu(pMenuTest1);
        pMenuBar->addSeparator();    //分隔栏
        ui->horizontalLayout->addWidget(pMenuBar);

}

void Menu::signal_slotConnection()
{
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(Open_Function(QTreeWidgetItem *, int)));
}

#include "menu.h"
#include "ui_menu.h"

#include <QDebug>
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    init();
    signal_slotConnection();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::Open_Function(QTreeWidgetItem *item, int column)
{
    qDebug() << item->text(0);
    if (QString::localeAwareCompare(item->text(0),"用户管理")==0){
        ui->stackedWidget->addWidget(User_Manage::getUser_Manage());
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(User_Manage::getUser_Manage()));
    }
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
}

void Menu::signal_slotConnection()
{
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),this,SLOT(Open_Function(QTreeWidgetItem *, int)));
}

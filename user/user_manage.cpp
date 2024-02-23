#include "user_manage.h"
#include "ui_user_manage.h"


User_Manage::User_Manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_Manage)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        update_data();
    });//连接信号槽
    timer->start(5000);//5s更新一次
    setTable();
    update_data();
}

User_Manage::~User_Manage()
{
    delete ui;
}

void User_Manage::setTable()
{
//    ui->tableWidget->setColumnCount(6);//设置列
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(5,QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见,即左边序号不见
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格内容不可编辑
    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
             "QScrollBar::add-line{background:transparent;}");



}

void User_Manage::update_data()
{
    QSqlQuery query = BroadcastMain::getData_Sheet("user");
    int number = query.size();
    int row = 0;
    if (number!=-1||number!=0){
        ui->tableWidget->setRowCount(number);//设置行
//        number=0;
        while(query.next()){
            for (int i=0;i<9;i++){
                QTableWidgetItem* item1 = new QTableWidgetItem(query.value(i).toString());
                ui->tableWidget->setItem(row,i,item1);
                if (i==7||i==8){
                    QTableWidgetItem* item1 = new QTableWidgetItem(query.value(i).toString().replace("T"," "));
                    ui->tableWidget->setItem(row,i,item1);
                }
            }
//            QTableWidgetItem* item1 = new QTableWidgetItem(query.value(0).toString());
//            QTableWidgetItem* item2 = new QTableWidgetItem(query.value(1).toString());
//            QTableWidgetItem* item3 = new QTableWidgetItem(query.value(2).toString());
//            QTableWidgetItem* item4 = new QTableWidgetItem(query.value(3).toString());
//            QTableWidgetItem* item5 = new QTableWidgetItem(query.value(4).toString());
//            QTableWidgetItem* item6 = new QTableWidgetItem(query.value(5).toString());
//            ui->tableWidget->setItem(number,0, item1);
//            ui->tableWidget->setItem(number,1, item2);
//            ui->tableWidget->setItem(number,2, item3);
//            ui->tableWidget->setItem(number,3, item4);
//            ui->tableWidget->setItem(number,4, item5);
//            ui->tableWidget->setItem(number,5, item6);
            row++;
        }
    }
}

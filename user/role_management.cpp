#include "role_management.h"
#include "ui_role_management.h"

Role_management::Role_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Role_management)
{
    ui->setupUi(this);
    setTable();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        update_data();
    });//连接信号槽
    timer->start(5000);//5s更新一次
    update_data();
}

Role_management::~Role_management()
{
    delete ui;
}

void Role_management::setTable()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见,即左边序号不见
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置表格内容不可编辑
    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 12px;}"
             "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
             "QScrollBar::handle:hover{background:gray;}"
             "QScrollBar::sub-line{background:transparent;}"
                                                        "QScrollBar::add-line{background:transparent;}");
}

void Role_management::update_data()
{
    QSqlQuery query = BroadcastMain::getData_Sheet("role");
    int number = query.size();
    int row = 0;
    if (number!=-1||number!=0){
        ui->tableWidget->setRowCount(number);//设置行
//        number=0;
        while(query.next()){
            for (int i=0;i<4;i++){
                QTableWidgetItem* item1 = new QTableWidgetItem(query.value(i).toString());
                ui->tableWidget->setItem(row,i,item1);
                if (i==2||i==3){
                    QTableWidgetItem* item1 = new QTableWidgetItem(query.value(i).toString().replace("T"," "));
                    ui->tableWidget->setItem(row,i,item1);
                }
            }
            row++;
        }
    }
}

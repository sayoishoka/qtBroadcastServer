#include "user_manage.h"
#include "ui_user_manage.h"


User_Manage *User_Manage::a = nullptr;
User_Manage::User_Manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_Manage)
{
    ui->setupUi(this);
}

User_Manage::~User_Manage()
{
    delete ui;
}

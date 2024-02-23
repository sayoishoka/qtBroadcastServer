#include "rights_management.h"
#include "ui_rights_management.h"

Rights_management::Rights_management(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rights_management)
{
    ui->setupUi(this);
}

Rights_management::~Rights_management()
{
    delete ui;
}

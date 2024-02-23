#ifndef ADDUSER_H
#define ADDUSER_H

#include <QWidget>

namespace Ui {
class AddUser;
}

class AddUser : public QWidget
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    ~AddUser();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H

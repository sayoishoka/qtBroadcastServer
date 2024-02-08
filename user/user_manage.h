#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include <QWidget>

namespace Ui {
class User_Manage;
}

class User_Manage : public QWidget
{
    Q_OBJECT

public:
    explicit User_Manage(QWidget *parent = nullptr);
    ~User_Manage();

    static User_Manage* getUser_Manage(){
        if (a == nullptr) {
            a = new User_Manage;
        }
        return a;
    };
private:
    static User_Manage* a;
    Ui::User_Manage *ui;
};

#endif // USER_MANAGE_H

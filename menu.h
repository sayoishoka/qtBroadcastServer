#ifndef MENU_H
#define MENU_H

#include "user/user_manage.h"

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void Open_Function(QTreeWidgetItem *item, int column);
private:
    void init();
    void signal_slotConnection();
    User_Manage *user_mange = new User_Manage();
    Ui::Menu *ui;
};

#endif // MENU_H

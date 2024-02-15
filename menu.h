#ifndef MENU_H
#define MENU_H

#include "user/user_manage.h"

#include <QWidget>
#include <QTreeWidgetItem>
#include <QMenuBar>
#include <QDateTime>
#include <QTimer>
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
    void timerr();//定时器
    void init();
    void signal_slotConnection();
    //菜单栏
    QMenuBar *pMenuBar;
    //菜单项
    QMenu *pMenuTest1;
    //子菜单
    QAction *pActionTest1;
    QAction *pActionTest2;
    QAction *pActionTest3;
    QAction *pActionTest4;

    QList<QAction*> list1;
    User_Manage *user_mange = new User_Manage();
    Ui::Menu *ui;
};

#endif // MENU_H

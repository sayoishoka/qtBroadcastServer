#ifndef RIGHTS_MANAGEMENT_H
#define RIGHTS_MANAGEMENT_H

#include <QWidget>

namespace Ui {
class Rights_management;
}

class Rights_management : public QWidget
{
    Q_OBJECT

public:
    static Rights_management* getRights_management(){
        static Rights_management instance;
        return &instance;
    };

    ~Rights_management();

private:
    explicit Rights_management(QWidget *parent = nullptr);
    Ui::Rights_management *ui;
};

#endif // RIGHTS_MANAGEMENT_H

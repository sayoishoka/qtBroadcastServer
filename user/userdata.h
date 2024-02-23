#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
class User {
public:
    int id;
    QString name;
    QString accountnumber;
    QString password;
    QString role;
    QString status;
};

class logon_user{
public:
    int id;
    QString name;
    QString accountnumber;
    QString password;
    QString role;
    QString status;
};

#endif // USERDATA_H

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databaseconfig.cpp \
    main.cpp \
    broadcastmain.cpp \
    menu.cpp \
    tcplink.cpp \
    user/add/adduser.cpp \
    user/rights_management.cpp \
    user/role_management.cpp \
    user/user_manage.cpp
HEADERS += \
    broadcastmain.h \
    databaseconfig.h \
    dispatcher.h \
    menu.h \
    tcplink.h \
    user/add/adduser.h \
    user/rights_management.h \
    user/role_management.h \
    user/user_manage.h \
    user/userdata.h
FORMS += \
    broadcastmain.ui \
    databaseconfig.ui \
    menu.ui \
    user/add/adduser.ui \
    user/rights_management.ui \
    user/role_management.ui \
    user/user_manage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

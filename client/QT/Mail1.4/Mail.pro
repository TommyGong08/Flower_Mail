#-------------------------------------------------
#
# Project created by QtCreator 2020-09-12T22:19:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mail
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
     main.cpp \
    loginwindow.cpp \
    registerwindow.cpp \
    mainwindow.cpp \
    widget.cpp \
    al_send_widget.cpp \
#    checkfile.cpp \
    contact.cpp \
    textcontact.cpp \
    writemail.cpp \
    policies.cpp \
    mailwidget.cpp \
    checkfile.cpp \
    checkrecv.cpp \
    ClientSocket.cpp \
    ContactModule.cpp \
    Login.cpp \
    ReceiveModule.cpp \
    Register.cpp \
    WriteModule.cpp
#    ../../client/Module/source/Login.c \
 #   ../../client/Module/source/ClientSocket.c \
#    ../../client/Module/source/ContactModule.c \
#    ../../client/Module/source/ReceiveModule.c \
#    ../../client/Module/source/Register.c \
#    ../../client/Module/source/WriteModule.c

HEADERS += \
    loginwindow.h \
    registerwindow.h \
    mainwindow.h \
    mailwidget.h \
    widget.h \
    al_send_widget.h \
    contact.h \
    textcontact.h \
    writemail.h \
    policies.h \
    mailwidget.h \
    register.h \
    write.h \
    checkfile.h \
    checkrecv.h \
    ClientSocket.h \
    ContactModule.h \
    Login.h \
    ReceiveModule.h \
    Register.h \
    WriteModule.h \
    Struct.h
#    ../../client/Module/include/ClientSocket.h \
#    ../../client/Module/include/ContactModule.h \
#    ../../client/Module/include/Login.h \
#    ../../client/Module/include/ReceiveModule.h \
#    ../../client/Module/include/Register.h \
#    ../../client/Module/include/Struct.h \
#    ../../client/Module/include/WriteModule.h

FORMS += \
    loginwindow.ui \
    registerwindow.ui \
    mainwindow.ui \
    widget.ui \
    al_send_widget.ui \
    contact.ui \
    textcontact.ui \
    writemail.ui \
    policies.ui \
    checkfile.ui \
    checkrecv.ui

DISTFILES +=

RESOURCES += \
    logo.qrc

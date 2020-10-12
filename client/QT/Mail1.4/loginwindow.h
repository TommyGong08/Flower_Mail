#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QDebug>
#include "registerwindow.h"
#include "mainwindow.h"
//#include "/home/liusiyuan/Desktop/client/Module/include/Login.h"


namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

//    int CheckLoginInput(char* UserName, char* PsWd){
//        return 0;
//    }

//    int SendLoginUserInfoToServer(char* UserName , char* PsWd){
//        return 0;
//    }

//    int SendLoginStateToServer(char* UserName){

//    }

//    int CreaterUserFolder(char* UserName){
////        qDebug()<<"login username"<<UserName;
//    }

private slots:
    void on_LoginBtn_login_clicked();

    void on_SignUpBtn_login_clicked();

    void loginOpen(QString x,QString y);

    void loginBack();

    void mainBack();

signals:
    void emitUsN(QString a);

private:
    Ui::LoginWindow *ui;
    RegisterWindow re;
    MainWindow ma;
    typedef struct UserInfo
    {
        char * UserName;                 //用户名不超过20个字符
        char * Password;                 //密码不超过20
        char * Telephone;                //用户手机号码
        int    LoginState;                                   //用户登陆状态：1表示未登陆，0表示已经登陆
    }userinfo;
};

#endif // LOGINWINDOW_H

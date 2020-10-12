#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
//#include "register.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();

//    int CheckRegisterInput(char* UserName, char* Password, char* Telephone){
//        return 0;
//    }

//    int SendRegisterUserInfoToServer(char* UserName, char* Password,
//                                     int LoginState, char* Telephone){
//        return 0;
//    }

//    int SendUserIdToServer(char* UserId){
//        return 0;
//}

private slots:
    void on_signUp_btn_register_clicked();

    void on_quit_btn_register_clicked();

signals:
    void registerClose(QString a,QString b);

    void backToLogin();

private:
    Ui::RegisterWindow *ui;
    typedef struct userInfo
    {
        char * UserName;                 //用户名不超过20个字符
        char * Password;                 //密码不超过20
        char * Telephone;                //用户手机号码
        int    LoginState;                                   //用户登陆状态：1表示未登陆，0表示已经登陆
    }userInfo;
    userInfo user;
};

#endif // REGISTERWINDOW_H

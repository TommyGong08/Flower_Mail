#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "loginwindow.h"
#include "QDebug"
//#include "register.h"
#include "Register.h"
#include "ClientSocket.h"


RegisterWindow::RegisterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}


/*
 * check UserName/Password/RePassWord isEmpty | isIlegal | isExist
 * Y-> try again
 * N-> close RegisterWindow and open LoginWindow
 *
 * !！shortcome:can only check isEmpty when click the btn "login"
 */
void RegisterWindow::on_signUp_btn_register_clicked()
{
        ui->UsN_alert_register->setText("");
        ui->PsW_alert_register->setText("");
        ui->RePsW_alert_register->setText("");
        QString UsN_register_QStr = ui->UsN_line_register->text();
        QString PsW_register_QStr = ui->PsW_line_register->text();
        QString RePsW_register_QStr = ui->RePsW_line_register->text();
        QByteArray UsN_register_ba = UsN_register_QStr.toLatin1();
        char *UsN_register_Ch = UsN_register_ba.data();
        QByteArray PsW_register_ba = PsW_register_QStr.toLatin1();
        char *PsW_register_Ch = PsW_register_ba.data();
        QByteArray Re_PsW_register_ba = RePsW_register_QStr.toLatin1();
        char *RePsW_register_Ch = Re_PsW_register_ba.data();
        if(UsN_register_QStr == "" || PsW_register_QStr == ""
                || RePsW_register_QStr == ""){
            if(UsN_register_QStr == ""){
                ui->UsN_alert_register->setText("UserName is empty!");
            }
            if(PsW_register_QStr == ""){
                ui->PsW_alert_register->setText("Password is empty!");
            }
            if(RePsW_register_QStr == ""){
                ui->RePsW_alert_register->setText("Re-Password is empty!");
            }
        }else{
            if(strcmp(PsW_register_Ch,RePsW_register_Ch) != 0){
                ui->RePsW_alert_register->setText("两次密码不一致!");
            }else{
                user.UserName = UsN_register_Ch;
                user.Password = PsW_register_Ch;
                user.LoginState = 1;
                qDebug()<<"hello1";
                int res = CheckRegisterInput(user.UserName, user.Password, user.Telephone);
                if(res != 0){
                    ui->RePsW_alert_register->setText("UserName or PassWord is invalid!");
                }else{
                    qDebug()<<"hello4";
                    int res2 = SendUserIdToServer(UsN_register_Ch);
                    qDebug()<<res2;
                    qDebug()<<"hello2";
                    if(res2 !=0){
                        ui->UsN_alert_register->setText("UserName is already exist!");
                    }else{
                        int res3 = SendRegisterUserInfoToServer(user.UserName, user.Password, user.LoginState, user.Telephone);
                        if(res3 == 0){
                            emit registerClose(UsN_register_QStr,PsW_register_QStr);
                            qDebug()<<"hello3";
                            this->close();
                        }
                    }
                }
            }
        }
}

void RegisterWindow::on_quit_btn_register_clicked()
{
    emit backToLogin();
    this->close();
}

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "ui_registerwindow.h"
#include "QDebug"
//#include "struct.h"
#include "Login.h"
#include "WriteModule.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

     /*
      * back to LoginWindow
      */
    void(RegisterWindow:: *registerSignal)(QString,QString) = &RegisterWindow::registerClose;
    void(LoginWindow:: *loginSlot)(QString,QString) = &LoginWindow::loginOpen;
    qDebug()<<"connect login & register";
    connect(&re,registerSignal,this,loginSlot);

    void(RegisterWindow:: *reBackSignal)(void) = &RegisterWindow::backToLogin;
    void(LoginWindow:: *loBackSlot)(void) = &LoginWindow::loginBack;
    connect(&re,reBackSignal,this,loBackSlot);

    void(MainWindow:: *mainQuitSignal)(void) = &MainWindow::quitToLogin;
    void(LoginWindow:: *loSlot)(void) = &LoginWindow::mainBack;
    connect(&ma,mainQuitSignal,this,loSlot);

    void(LoginWindow:: *loginClose_Signal)(QString) = &LoginWindow::emitUsN;
    void(MainWindow:: *mainOpen_Slot)(QString) = &MainWindow::main_UsN;
    connect(this,loginClose_Signal,&ma,mainOpen_Slot);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loginBack(){
    ui->UsNLine_login->setText("");
    ui->PsWLine_login->setText("");
    this->show();
}

void LoginWindow::mainBack(){
    ui->UsNLine_login->setText("");
    ui->PsWLine_login->setText("");
    this->show();
}

void LoginWindow::loginOpen(QString x, QString y){
    ui->UsNLine_login->setText(x);
    ui->PsWLine_login->setText(y);
    this->show();
}

/*
 * check UserName and Password isEmpty | isIlegal | isMAtch
 * Y-> close LoginWindow and open MainWindow
 * N-> alert and rewrite
 *
 * !！shortcome:can only check isEmpty when click the btn "login"
 */

void LoginWindow::on_LoginBtn_login_clicked()
{
    QString UsN_login_QStr = ui->UsNLine_login->text();
    QString PsW_login_QStr = ui->PsWLine_login->text();
    ui->UsNLabel_login_alert->setText("");
    ui->PsWLabel_login_alert->setText("");
    if(UsN_login_QStr == "" || PsW_login_QStr == ""){
        if(UsN_login_QStr == ""){
            ui->UsNLabel_login_alert->setText("UserName is empty!");
        }
        if(PsW_login_QStr == ""){
            ui->PsWLabel_login_alert->setText("Password is empty!");
        }
    }else{
        QByteArray UsN_login_ba = UsN_login_QStr.toLatin1();
        char *UsN_login_Ch = UsN_login_ba.data();
        QByteArray PsW_login_ba = PsW_login_QStr.toLatin1();
        char *PsW_login_Ch = PsW_login_ba.data();
        qDebug()<<UsN_login_Ch;
        qDebug()<<PsW_login_Ch;
        int res = CheckLoginInput(UsN_login_Ch,PsW_login_Ch);//success
        qDebug()<< res;
        switch (res) {
        case 0:{
            qDebug()<< "hello";
            int res2 = SendLoginUserInfoToServer(UsN_login_Ch,PsW_login_Ch);
            qDebug()<<res2;
            if(res2 < 0){
                ui->PsWLabel_login_alert->setText("UserName or PassWord is wrong!");
            }else{
                int res3 = SendLoginStateToServer(UsN_login_Ch);
                qDebug() << res3;
                if(res3 < 0){
                    ui->PsWLabel_login_alert->setText("You are already logged in!");
                }else{
                    this->close();
                    emit emitUsN(UsN_login_QStr);
                    qDebug() << UsN_login_Ch;
                  //  int createfolder = CreaterUserFolder(UsN_login_Ch);
                    ma.show();
                }
            }
            break;
        }
        case 1:
            ui->UsNLabel_login_alert->setText("UserName invalid!");
            break;
        default:
            ui->PsWLabel_login_alert->setText("PassWord invalid!");
            break;
        }
    }
}

/*
 * loop to the RegisterWindow and close the LoginWindow
 */
void LoginWindow::on_SignUpBtn_login_clicked()
{
    this->hide();
    re.show();
}

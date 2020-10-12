#include "checkrecv.h"
#include "ui_checkrecv.h"
//#include "struct.h"

checkRecv::checkRecv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkRecv)
{
    ui->setupUi(this);
    showEmail();
}

checkRecv::~checkRecv()
{
    delete ui;
}

void checkRecv::showEmail()
{
//    GetServerEmail(UserID);
    ui->emailID->setText("abasjdhakjf");
    ui->emailTime->setText("2020.10.9");
    ui->emailTheme->setText("gdfhdfdf");
    ui->emailContent->setText("dfgdsgj");
}

void checkRecv::on_filecheck_clicked()
{
//    GetAttachEmail(UserInfo.UserName,Re_MailInfo[Re_Count].EmailID);
}

void checkRecv::on_emailback_clicked()
{
    //跳转到写信界面
    //
}

void checkRecv::on_del_clicked()
{
//    DeleteServerEmail(Re_MailInfo[Re_Count].EmailID);
}

//void checkRecv::rece_sendInfo_wid(char *emailID){
//    email_send = emailID;
//    this->show();
//}

//void checkRecv::rece_timeInfo_wid(char *emailtime){
//    email_time = emailtime;
//}

//void checkRecv::rece_themeInfo_wid(char *emailtheme){
//    email_theme = emailtheme;
//}

//void checkRecv::rece_contectInfo_wid(char *emailcontect){
//    email_contect = emailcontect;
//}

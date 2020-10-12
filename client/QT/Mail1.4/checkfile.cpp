#include "checkfile.h"
#include "ui_checkfile.h"
//#include "struct.h"


checkfile::checkfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::checkfile)
{
    ui->setupUi(this);
    showContent();
}

checkfile::~checkfile()
{
    delete ui;
}

void checkfile::showContent()
{
    //****从数据库得到邮件信息，返回EmailInfo
    /*
    struct MailInfo EmailInfo; // mail结构体
    memset(&EmailInfo, 0, sizeof(EmailInfo));
    */

    ui->emailID->setText("Email ID: ");
    ui->emailID->setText("EmailInfo.EmailID");

    ui->emailContent->setText("EmailInfo.EmailContent");

    connect(ui->emailback, SIGNAL(clicked()), this, SLOT(on_clicked_back()));
}

void checkfile::on_clicked_back()
{

}

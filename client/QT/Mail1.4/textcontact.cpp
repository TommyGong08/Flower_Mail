#include "textcontact.h"
#include "ui_textcontact.h"
//#include "struct.h"
#include "ContactModule.h"
#include "QMessageBox"

textContact::textContact(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::textContact)
{
    ui->setupUi(this);
}

textContact::~textContact()
{
    delete ui;
}

void textContact::on_add_clicked()
{
    QString qID = ui->TextID->text();
    QByteArray fid = qID.toLatin1();
    char* FriendID = fid.data();
    QString uID = ui->UserID->text();
    QByteArray userid = uID.toLatin1();
    char* userID = userid.data();
    int ans = AddContact(userID , FriendID);
    if(ans==0){
    QMessageBox::information(NULL, "ADD", "Add Successful!");
    this->close();
    }
    else
    {
        QMessageBox::information(NULL, "ADD", "Fail!");
        this->close();
    }
    //qmessagebox
//    delete ui;
}



void textContact::on_quit_clicked()
{
    this->close();
//    delete ui;
}

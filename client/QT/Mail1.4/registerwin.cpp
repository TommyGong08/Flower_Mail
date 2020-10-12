#include "registerwin.h"
#include "ui_registerwin.h"

RegisterWin::RegisterWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWin)
{
    ui->setupUi(this);

    connect(ui->signUp_btn_register,&QPushButton::clicked,this,
            &RegisterWin::onClick_signUp_btn );
    connect(ui->quit_btn_register,&QPushButton::clicked,this,
            &RegisterWin::onClick_quit_btn);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::onClick_quit_btn(){
    this->close();
}

void RegisterWin::onClick_signUp_btn(){
    emit registerClose();
    //qDebug()<<"registerClose";
    //this->close();
}

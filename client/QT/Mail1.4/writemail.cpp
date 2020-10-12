#include "writemail.h"
#include "ui_writemail.h"
#include "WriteModule.h"
#include "ClientSocket.h"

#include <QString>
#include <QTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

writemail::writemail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::writemail)
{
    ui->setupUi(this);
    ui->chaosonglabel->hide();
    ui->getchaosong->hide();
    wr_mailinfo.IfAttachFile = 1;
    wr_mailinfo.EmailState = 1;
    wr_mailinfo.CopySendID = "NULL";
    wr_mailinfo.SecretSendID = "NULL";
    wr_mailinfo.EmailPath = "NULL";
}

writemail::~writemail()
{
    delete ui;
}

void writemail::on_misong_clicked()
{
    if(ui->misong->text()=="密送"){
        flag_mi_clicked = 1;
        ui->chaosonglabel->show();
        ui->getchaosong->show();
        ui->misong->setText("取消密送");
    }else{
        flag_mi_clicked = 0;
        ui->chaosonglabel->hide();
        ui->getchaosong->hide();
        ui->misong->setText("密送");
    }
}

void writemail::on_chaosong_clicked()
{
    if(ui->chaosong->text()=="抄送"){
        flag_chao_clicked = 1;
        ui->chaosonglabel->show();
        ui->getchaosong->show();
        ui->chaosong->setText("取消抄送");
    }else{
        flag_chao_clicked = 0;
        ui->chaosonglabel->hide();
        ui->getchaosong->hide();
        ui->chaosong->setText("抄送");
    }
}

void writemail::on_attachfile_clicked()
{
    wr_mailinfo.IfAttachFile = 0;

    file_full = QFileDialog::getOpenFileName(
            this,
            tr("open a file."),     //[选择文件夹]框的标题
            "D:/",                  //文件的默认目录,假设为D盘
            tr("All files(*.*)"));  //支持打开所有类型文件
    fileinfo = QFileInfo(file_full);
    file_name = fileinfo.fileName();//文件名
    file_path = fileinfo.absoluteFilePath();//绝对路径
    QByteArray path_QB = file_path.toLatin1();
    wr_mailinfo.EmailPath = path_QB.data();

    if (file_name.isEmpty()){     //打开空文件
        QMessageBox::warning(this, "Warning!", "Failed to open the file");
    }else{
        QByteArray FilePath = file_path.toLatin1();
        char* AttachFilePath = FilePath.data();
        LeadinAttachFile(AttachFilePath);
        char* text;
        qDebug()<<FilePath;

//            LeadinAttachFile(AttachFilePath, text);
            //****附件与socket连接的函数
        }
}

void writemail::on_send_clicked()
{
    if(flag_dra_clicked == 1){
        wr_mailinfo.EmailType = -2;
    }else if(flag_mi_clicked == 1 && flag_chao_clicked == 1){
        wr_mailinfo.EmailType = 3;//chao + mi
    }else if(flag_chao_clicked == 1){
        wr_mailinfo.EmailType = 1;//chao
    }else if(flag_mi_clicked == 1){
        wr_mailinfo.EmailType = 2;//mi
    }else{
        wr_mailinfo.EmailType = 0;//normal
        wr_mailinfo.CopySendID = "NULL";
        wr_mailinfo.SecretSendID = "NULL";
    }
    flag_dra_clicked = 0;
    flag_chao_clicked = 0;
    flag_mi_clicked = 0;

    // 获取IP、端口号、收件人ID、邮件标题、邮件内容
    // 将收件人ID、邮件主题、邮件内容写入结构体
    QString qemailID = ui->emailID->text();
    QByteArray mailID_QB = qemailID.toLatin1();
    wr_mailinfo.EmailReceiver = mailID_QB.data();
    QString qtheme = ui->emailTheme->text();
    QByteArray theme_QB = qtheme.toLatin1();
    wr_mailinfo.EmailTheme = theme_QB.data();
    QString mail_rece = ui->getchaosong->text();
    QByteArray mailrece_QB = mail_rece.toLatin1();
    if(wr_mailinfo.EmailType == 1)
    {
        wr_mailinfo.CopySendID = mailrece_QB.data();
    }
    else if(wr_mailinfo.EmailType == 2)
    {
        wr_mailinfo.SecretSendID = mailrece_QB.data();
    }
    else
    {
        wr_mailinfo.CopySendID = mailrece_QB.data();
        wr_mailinfo.SecretSendID = mailrece_QB.data();
    }

     qDebug() << wr_mailinfo.CopySendID;
    wr_mailinfo.EmailSender = "TT12345";

    // 获取text
    QString qcontent = ui->emailContent->toPlainText();
    QByteArray content_QB = qcontent.toLatin1();
    char* text = content_QB.data();
    qDebug()<< text;

    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
    QByteArray time_QB = localTime.toLatin1();
    wr_mailinfo.EmailSystemTime = time_QB.data();

    //send
   /*qDebug()<< wr_mailinfo.EmailPath;
     qDebug()<< wr_mailinfo.CopySendID;
     qDebug()<< wr_mailinfo.SecretSendID;
     qDebug()<< wr_mailinfo.AttachFilePath;
     qDebug()<< wr_mailinfo.EmailSender;
     qDebug()<< wr_mailinfo.EmailReceiver;*/
    qDebug()<< wr_mailinfo.IfAttachFile;
         qDebug()<<"xx" << wr_mailinfo.EmailTheme;
    int  sendmail = SendEmail(wr_mailinfo.EmailID, wr_mailinfo.EmailTheme,
              wr_mailinfo.EmailPath, wr_mailinfo.EmailType,
              wr_mailinfo.EmailState, wr_mailinfo.CopySendID,
              wr_mailinfo.SecretSendID, wr_mailinfo.EmailSystemTime,
              wr_mailinfo.IfAttachFile, wr_mailinfo.AttachFilePath,
              wr_mailinfo.EmailSender, wr_mailinfo.EmailReceiver, text);
    qDebug() << "yyyy"<<sendmail ;
    ui->emailTheme->setText("");
    ui->getchaosong->setText("");
    ui->emailContent->setText("");
    ui->emailID->setText("");
}

void writemail::on_draft_clicked()
{

    flag_dra_clicked = 1;

    // 收件人ID、邮件标题、邮件内容
    QString qemailID = ui->emailID->text();
    QByteArray mailID_QB = qemailID.toLatin1();
    wr_mailinfo.EmailReceiver = mailID_QB.data();
    QString qtheme = ui->emailTheme->text();
    QByteArray theme_QB = qtheme.toLatin1();
    wr_mailinfo.EmailTheme = theme_QB.data();
    QString qcontent = ui->emailContent->toPlainText();
//    qDebug()<<"content"<<qcontent;
    QByteArray content = qcontent.toLatin1();
    char* text = content.data();
//    SendEmail(wr_mailinfo, text);

//    SaveDraft(MailInfo* EmailInfo, char* text); //存草稿的函数 socket
}

void writemail::on_close_clicked()
{
    //页面关闭
}

void writemail::write_UsN(QString x){
    UserName = x;
    //获取系统时间
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
    QByteArray time_QB = localTime.toLatin1();
    wr_mailinfo.EmailSystemTime = time_QB.data();
    qDebug() << localTime;

    //拼接emailID
    UserName.append(localTime);
    QByteArray mail_id_QB = UserName.toLatin1();
    wr_mailinfo.EmailID = mail_id_QB.data();
    qDebug()<<"init e_ID"<<wr_mailinfo.EmailID;

    QByteArray usn_QB = x.toLatin1();
    wr_mailinfo.EmailWriteID = usn_QB.data();
    wr_mailinfo.EmailSender = usn_QB.data();
    qDebug()<<"write"<<wr_mailinfo.EmailSender;

}

#include "widget.h"
#include "ui_widget.h"
//#include "struct.h"
#include "ReceiveModule.h"
#include "ClientSocket.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QTableView>
#include <QPushButton>
#include <checkrecv.h>
#include <QVariant>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct DataStruct
{
    char SendID[100];
    char EmailID[100];
    char Theme[100];
    char EmailTime[100];
    char Info[100];
}data;
 data mydata[50];
typedef struct mailInfo
{
  char *  EmailWriteID = NULL;          //邮件编写者ID
  char *  EmailID = NULL;               //邮件ID
  char *  EmailTheme  = NULL;            //邮件主题
  char *  EmailPath = NULL;              //邮件在本地路径
  int   EmailType =0;                                //邮件类型 ： -2草稿，0发送，1抄送，2密送，3抄送+密送，
  int   EmailState= 0 ;                                //邮件状态 ：0保留，-1已读，1未读
  char *  EmailSender = NULL;           //邮件发送者
  char *  EmailContent = NULL;
  char *  EmailReceiver = NULL;         //邮件接受者
  char *  CopySendID = NULL;             //抄送用户ID，以分号作为分割
  char *  SecretSendID = NULL;           //密送用户ID，以分号作为分割
  char *  EmailSystemTime = NULL;       //邮件发送、接受、恢复、草稿等用同一个系统时间
  int   IfAttachFile = -1;                              //有无附件，0表示有，-1表示无
  char *  AttachFilePath = NULL;        // 附件存储路径
}ReMailInfo;

ReMailInfo Re_MailInfo[10];

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    void(Widget:: *senderInfo_rece_Signal)(char*)
//                = &Widget::senderInfo_to_check;
//        void(checkRecv:: *rece_senderInfo_Slot)(char*)
//                = &checkRecv::rece_sendInfo_wid;
//        connect(this,senderInfo_rece_Signal,&ch_r,rece_senderInfo_Slot);

//        void(Widget:: *timeInfo_rece_Signal)(char*)
//                = &Widget::timeInfo_to_check;
//        void(checkRecv:: *rece_timeInfo_Slot)(char*)
//                = &checkRecv::rece_timeInfo_wid;
//        connect(this,timeInfo_rece_Signal,&ch_r,rece_timeInfo_Slot);

//        void(Widget:: *themeInfo_rece_Signal)(char*)
//                = &Widget::themeInfo_to_check;
//        void(checkRecv:: *rece_themeInfo_Slot)(char*)
//                = &checkRecv::rece_themeInfo_wid;
//        connect(this,themeInfo_rece_Signal,&ch_r,rece_themeInfo_Slot);

//        void(Widget:: *contectInfo_rece_Signal)(char*)
//                = &Widget::timeInfo_to_check;
//        void(checkRecv:: *rece_contectInfo_Slot)(char*)
//                = &checkRecv::rece_timeInfo_wid;
//        connect(this,contectInfo_rece_Signal,&ch_r,rece_contectInfo_Slot);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
    {
        QStandardItemModel* model = new QStandardItemModel(this);
        model->setColumnCount(6);
        model->setHeaderData(0,Qt::Horizontal, "发件人");
        model->setHeaderData(1,Qt::Horizontal, "邮件主题");
        model->setHeaderData(2,Qt::Horizontal, "时间");
        model->setHeaderData(3,Qt::Horizontal, "已读");
        model->setHeaderData(4,Qt::Horizontal, "查看");
        model->setHeaderData(5,Qt::Horizontal, "删除");

        ui->tableView->setModel(model);

        ui->tableView->setColumnWidth(0, 100);    //设置列的宽度
        ui->tableView->setColumnWidth(1, 300);
        ui->tableView->setColumnWidth(2, 100);
        ui->tableView->setColumnWidth(3, 50);
        ui->tableView->setColumnWidth(4, 50);
        ui->tableView->setColumnWidth(5, 50);

        //UserName = ui->usn->text();
        //qDebug() << UserName.toLatin1();
        //serName = str("Mary12345");
        QByteArray user_QB = UserName.toLatin1();
        //qDebug() << user_QB ;
        char* user_char = user_QB.data();
      //  qDebug()<< user_QB.data();
       //char* text =  "hgcch|fchch|gfdhcfhc|fheidfhee|djddjdic|";//GetServerEmail(user_char);
     //   qDebug() << user_char;
            char* text = GetServerEmail(user_char);
         //   qDebug() << text;
            int Re_Count = GetServerStringDisintergrate(text);
            for(int i=0;i<Re_Count;i++)
            {
                qDebug()<<"i"<<i;
                qDebug()<<"sender"<<Re_MailInfo[i].EmailSender;
                qDebug()<<"theme"<<Re_MailInfo[i].EmailTheme;
                qDebug()<<"time"<<Re_MailInfo[i].EmailSystemTime;
                QString email_sender = QString("%1").arg(Re_MailInfo[i].EmailSender);
                QString email_theme = QString("%1").arg(Re_MailInfo[i].EmailTheme);
                QString email_time = QString("%1").arg(Re_MailInfo[i].EmailSystemTime);
                model->setItem(i, 0, new QStandardItem(email_sender));
                model->setItem(i, 1, new QStandardItem(email_theme));
                model->setItem(i, 2, new QStandardItem(email_time));

                QPushButton *ButtonRead = new QPushButton("已读"); //add new button
                ButtonRead->setProperty("row",i);
                connect(ButtonRead, SIGNAL(clicked()), this, SLOT(on_clicked_read()));

                QPushButton *ButtonCheck = new QPushButton("查看"); //add new button
                ButtonCheck->setProperty("row",i);
                connect(ButtonCheck, SIGNAL(clicked()), this, SLOT(on_clicked_ckeck()));

                QPushButton *ButtonDelect = new QPushButton("删除"); //add new button
                ButtonDelect->setProperty("row",i);
                connect(ButtonDelect, SIGNAL(clicked()), this, SLOT(on_clicked_delect()));

                ui->tableView->setIndexWidget(model->index(model->rowCount()-1,3),ButtonRead);
                ui->tableView->setIndexWidget(model->index(model->rowCount()-1,4),ButtonCheck);
                ui->tableView->setIndexWidget(model->index(model->rowCount()-1,5),ButtonDelect);
            }
    }

int GetServerStringDisintergrate(char* cmd)
{
  //  qDebug() << "new: "<< cmd;
    char text_in[1024];
    strcpy(text_in,cmd);
    char data[1024] = { 0 };
    char data_in[1024] = { 0 };
    char mes[100][100] = { 0 };
    int temp = 0;
    int flag = 0;
    int num = 0;
   // qDebug() << text_in[1];
    while(text_in[temp] != '\0')
    {
       // qDebug()<< "1";
        while (text_in[flag] != '#' && text_in[flag] != '\0')
        {
       //     qDebug() << "2";
            flag++;
           // qDebug()<<flag;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, text_in + temp, flag - temp);
        flag++;
        temp = flag;
        int temp_in = 0;
        int flag_in = 0;
        int num_in = 0;
        memset(mes,'\0',sizeof(mes));
        while(data[temp_in] != '\0')
        {
          //  qDebug() << "3";
            while(data[flag_in] != '|' && data[flag_in] !='\0')
            {
                flag_in++;
            }
            memset(data_in, '\0', sizeof(data_in));
            strncpy(data_in, data + temp_in, flag_in - temp_in);
            strcpy(mes[num_in], data_in);
            num_in++;
         //   qDebug() << num_in;
            flag_in++;
            temp_in = flag_in;
        }
        qDebug()<<"num is"<<num;
        strcpy(mydata[num].SendID, mes[0]);
        Re_MailInfo[num].EmailSender = mydata[num].SendID;
        qDebug ()<< Re_MailInfo[num].EmailSender;
        strcpy(mydata[num].EmailID, mes[1]);
        Re_MailInfo[num].EmailID = mydata[num].EmailID;
        qDebug ()<< Re_MailInfo[num].EmailID;
        strcpy(mydata[num].Theme, mes[2]);
        Re_MailInfo[num].EmailTheme = mydata[num].Theme;
        qDebug ()<< Re_MailInfo[num].EmailTheme;
        strcpy(mydata[num].EmailTime, mes[3]);
        Re_MailInfo[num].EmailSystemTime = mydata[num].EmailTime;
        qDebug ()<< Re_MailInfo[num].EmailSystemTime;
        strcpy(mydata[num].Info, mes[4]);
        Re_MailInfo[num].EmailContent = mydata[num].Info;
        qDebug ()<< Re_MailInfo[num].EmailContent;
        num++;
    }
 //   qDebug() << num;
    return num;
}

void Widget::on_clicked_read()
{
    QPushButton *btn = (QPushButton *)sender();
    int row = btn->property("row").toInt();
    //qDebug()<<"emit clicked";
    //emit check_btn_clicked(row);
    //ChangeEmailState(Re_MailInfo[row].EmailID);
}

void Widget::on_clicked_check()
{
    QPushButton *btn = (QPushButton *)sender();
        int row = btn->property("row").toInt();
        qDebug()<<"row"<<row;
        ch_r.show();
//        emit senderInfo_to_check(Re_MailInfo[row].EmailSender);
//        emit timeInfo_to_check(Re_MailInfo[row].EmailSystemTime);
//        emit themeInfo_to_check(Re_MailInfo[row].EmailTheme);
//        emit contectInfo_to_check(Re_MailInfo[row].EmailContent);

}

void Widget::on_clicked_delect()
{
    QPushButton *btn = (QPushButton *)sender();
    int row = btn->property("row").toInt();
    //DeleteServerEmail(Re_MailInfo[row].EmailID);
}

void Widget::rece_UsN(QString x){
//    UserName = x;
    qDebug()<<"rece"<<UserName;
}

void Widget::on_ok_clicked()
{
     UserName = ui->usn->text();
      init();
      qDebug()<<"usn"<<UserName;
}

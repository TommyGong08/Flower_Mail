#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
//#include "struct.h"
#include "Login.h"
#include "ContactModule.h"

char contact_list[100][100] = {0};

typedef struct RMailInfo
{
  char *  EmailWriteID;          //邮件编写者ID
  char *  EmailID;               //邮件ID
  char *  EmailTheme;            //邮件主题
  char *  EmailPath;              //邮件在本地路径
  int   EmailType ;                                //邮件类型 ： -2草稿，0发送，1抄送，2密送，3抄送+密送，
  int   EmailState;                                //邮件状态 ：0保留，-1已读，1未读
  char *  EmailSender;           //邮件发送者
  char *  EmailContent;
  char *  EmailReceiver;         //邮件接受者
  char *  CopySendID;             //抄送用户ID，以分号作为分割
  char *  SecretSendID;           //密送用户ID，以分号作为分割
  char *  EmailSystemTime;       //邮件发送、接受、恢复、草稿等用同一个系统时间
  int   IfAttachFile;                              //有无附件，0表示有，-1表示无
  char *  AttachFilePath;        // 附件存储路径
}reMailInfo;
reMailInfo con_MailInfo[10];

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    write_ui = new writemail(this);
    alSend_ui = new al_send_Widget(this);
    receive_ui = new Widget(this);
    QGridLayout *grid = new QGridLayout(ui->scrollArea);
    grid->addWidget(write_ui);
    grid->addWidget(alSend_ui);
    grid->addWidget(receive_ui);
    ui->scrollArea->setLayout(grid);
    write_ui->setVisible(false);
    alSend_ui->setVisible(false);
    receive_ui->setVisible(false);

//    contact_ui = new contact(this);
//    QGridLayout *con_grid = new QGridLayout(ui->addr_scroll);
//    con_grid->addWidget(contact_ui);
//    ui->addr_scroll->setLayout(con_grid);

    void(al_send_Widget:: *checkSignal)(QString) = &al_send_Widget::check_btn_clicked;
    void(MainWindow:: *mainSlot)(void) = &MainWindow::alSend_check_btn_clicked;
    qDebug()<<"connect main & check";
    connect(&check_btn,checkSignal, this, mainSlot);

    void(MainWindow:: *emit_Signal_rece)(QString) = &MainWindow::emitUsN_rece;
    void(Widget:: *emit_rece_Slot)(QString) = &Widget::rece_UsN;
    connect(this,emit_Signal_rece,&emit_usn_rece,emit_rece_Slot);

    void(MainWindow:: *emit_Signal_write)(QString) = &MainWindow::emitUsN_write;
    void(writemail:: *emit_write_Slot)(QString) = &writemail::write_UsN;
    connect(this,emit_Signal_write,&emit_usn_write,emit_write_Slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * turn to widget.ui
 */
void MainWindow::on_write_btn_main_clicked()
{
    qDebug()<<"click write";
    emit emitUsN_write(UserName);
    receive_ui->setVisible(false);
    alSend_ui->setVisible(false);
    write_ui->setVisible(true);
}

/*
 * turn to al_send_widget.ui
 */
void MainWindow::on_alSend_btn_main_clicked()
{
    qDebug()<<"click send";
    receive_ui->setVisible(false);
    write_ui->setVisible(false);
    alSend_ui->setVisible(true);
}


void MainWindow::alSend_check_btn_clicked(){
    check_ui = new checkfile(this);
    qDebug()<<"show checkfile";
//    this->ui->scrollArea->setWidget(check_ui);
}

/*
 * turn to receive.ui
 */
void MainWindow::on_receive_btn_main_clicked()
{
    qDebug()<<"click receive";
    emit emitUsN_rece(UserName);
    alSend_ui->setVisible(false);
    write_ui->setVisible(false);
    receive_ui->setVisible(true);
}

/*
 * back to loginWindow
 */
void MainWindow::on_Quit_clicked()
{
    this->close();
    emit quitToLogin();
    QByteArray temp_usn = UserName.toLatin1();
    SendLogOutInfoToServer(temp_usn.data());
}

void MainWindow::main_UsN(QString x){
    UserName = x;
}

int MainWindow::GetNameStringDisintergrate(char* cmd)
{

    char data[1024] = { 0 };
    char data_in[1024] = { 0 };
    char mes[100] = { 0 };
    int temp = 0;
    int flag = 0;
    int num = 0;
    char* text = cmd;
    while (text[temp] != '\0')
    {
        while (text[flag] != '#' && text[flag] != '\0')
        {
            flag++;
        }
        memset(data, '\0', sizeof(data));
        strncpy(data, text + temp, flag - temp);
        flag++;
        temp = flag;
        memset(mes,'\0',sizeof(mes));
        strcpy(contact_list[num], mes);
        con_MailInfo[num].EmailSender = contact_list[num];
        num++;
    }
    return num;
}

void MainWindow::listContact()
{
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(2);

    ui->tableView->setModel(model);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑

    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,50);

    QByteArray con_username = UserName.toLatin1();
    char* c_nsername = con_username.data();

    char* text = GetContactInfo(c_nsername);
    int row_count = GetNameStringDisintergrate(text);

    for(int i=0;i<row_count;i++)
    {
        QString emailsender = QString("%1").arg(con_MailInfo[i].EmailSender);
        model->setItem(i,0,new QStandardItem(emailsender));

        QPushButton *del = new QPushButton("x");
        connect(del, SIGNAL(clicked()), this, SLOT(on_del_clicked));
        del->setProperty("row",i);
        ui->tableView->setIndexWidget(model->index(model->rowCount()-1,1),del);
    }
}

void MainWindow::on_addContact_clicked()
{
    text_ui.show();
}

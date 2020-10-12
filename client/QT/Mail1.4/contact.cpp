//#include "contact.h"
//#include "ui_contact.h"
//#include "struct.h"

//#include <QStandardItemModel>
//#include <QDebug>
//#include <QTableView>
//#include <QPushButton>
//#include <QMessageBox>

//contact::contact(QWidget *parent) :
//    QWidget(parent),
//    ui(new Ui::contact)
//{
//    ui->setupUi(this);
//    listContact();
//}

//contact::~contact()
//{
//    delete ui;
//}

//void contact::listContact()
//{
//    QStandardItemModel* model = new QStandardItemModel(this);
//    model->setColumnCount(2);

//    ui->ContactList->setModel(model);

//    ui->ContactList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑

//    ui->ContactList->setColumnWidth(0,150);
//    ui->ContactList->setColumnWidth(1,50);

//    for(int i=0;i<5;i++)
//    {
//        model->setItem(i,0,new QStandardItem("EmailInfo.EmailID"));

//        QPushButton *del = new QPushButton("x");
//        connect(del, SIGNAL(clicked()), this, SLOT(on_del_clicked));
//        del->setProperty("row",i);
//        ui->ContactList->setIndexWidget(model->index(model->rowCount()-1,1),del);
//    }
//}

//void contact::on_del_clicked()
//{
//    QPushButton *btn = (QPushButton *)sender();
//    QString row = btn->property("row").toString();
//    //调用删除联系人的函数
//}

//void contact::on_addContact_clicked()
//{
//    text_ui.show();
//}

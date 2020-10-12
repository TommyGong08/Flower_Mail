#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>
#include "checkrecv.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void init();
//    int GetServerStringDisintergrate(char* cmd){
//        return 0;
//    }
//    char* GetServerEmail(char* UserName)
//    {
//        return 0;
//    }

private slots:
    void on_clicked_read();
    void on_clicked_delect();
    void on_clicked_check();

    void on_ok_clicked();

public slots:
    void rece_UsN(QString x);

//signals:
//    void senderInfo_to_check(char *emailID);
//    void timeInfo_to_check(char *emailtime);
//    void themeInfo_to_check(char *emailtheme);
//    void contectInfo_to_check(char *emailcontect);

private:
    Ui::Widget *ui;
    QString UserName;
    checkRecv ch_r;

};

#endif // WIDGET_H

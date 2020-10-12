#ifndef CHECKRECV_H
#define CHECKRECV_H

#include <QWidget>

namespace Ui {
class checkRecv;
}

class checkRecv : public QWidget
{
    Q_OBJECT

public:
    explicit checkRecv(QWidget *parent = 0);
    ~checkRecv();
    void showEmail();

private slots:
    void on_filecheck_clicked();

    void on_emailback_clicked();

    void on_del_clicked();

//public slots:
//    void rece_sendInfo_wid(char *emailID);
//    void rece_timeInfo_wid(char *emailtime);
//    void rece_themeInfo_wid(char *emailtheme);
//    void rece_contectInfo_wid(char *emailcontect);

//signals:
//    void checkOpen_sig();

private:
    Ui::checkRecv *ui;
//    char *email_send;
//    char *email_time;
//    char *email_theme;
//    char *email_contect;
};

#endif // CHECKRECV_H

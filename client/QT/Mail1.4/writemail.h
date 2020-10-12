#ifndef WRITEMAIL_H
#define WRITEMAIL_H



#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "write.h"


namespace Ui {
class writemail;
}

class writemail : public QWidget
{
    Q_OBJECT

public:
    explicit writemail(QWidget *parent = 0);
    ~writemail();

    char* LeadinAttachFile(char* AtthachFilePath){

    }

private slots:
    void on_chaosong_clicked();

    void on_misong_clicked();

    void on_attachfile_clicked();

    void on_send_clicked();

    void on_draft_clicked();

    void on_close_clicked();

// *   int SendEmail(char* EmailID,char* EmailTheme,char* EmailPath, int EmailType,
//                  int EmailState,char* CopySendID,char* SecretSendID,char* EmailSystemTime,
//                    int  IfAttachFile, char* AttachFilePath,char* EmailSender,
//                      char* EmailReceiver,char* text);*/



//    void on_chaosong_clicked(bool checked);

public slots:
    void write_UsN(QString x);

private:
    Ui::writemail *ui;
    int flag_chao_clicked = 0;
    int flag_mi_clicked = 0;
    int flag_dra_clicked = 0;
    QString UserName;
    MailIn wr_mailinfo;
    QString file_full, file_name, file_path;
    QFileInfo fileinfo;

};

#endif // WRITEMAIL_H

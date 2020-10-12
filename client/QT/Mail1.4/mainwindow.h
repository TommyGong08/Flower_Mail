#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "widget.h"
#include "al_send_widget.h"
#include "checkfile.h"
#include "contact.h"
#include "writemail.h"
#include "textcontact.h"
#include "ContactModule.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    ~on_write_btn_main_clicked();
    void SendLoginStateToServer(QString UserName);
    void listContact();
    int GetNameStringDisintergrate(char* cmd);

signals:
    void quitToLogin();

private slots:
    void on_write_btn_main_clicked();

    void on_alSend_btn_main_clicked();

    void alSend_check_btn_clicked();

    void on_Quit_clicked();

    void on_receive_btn_main_clicked();

    void on_addContact_clicked();

    //void on_del_clicked();

signals:
    void emitUsN_rece(QString a);

    void emitUsN_write(QString a);

public slots:
    void main_UsN(QString x);

private:
    Ui::MainWindow *ui;
    Widget *receive_ui;
    Widget emit_usn_rece;
    al_send_Widget *alSend_ui;
    checkfile *check_ui;
    al_send_Widget check_btn;
    writemail *write_ui;
    writemail emit_usn_write;
    QString UserName;
    textContact text_ui;
};

#endif // MAINWINDOW_H


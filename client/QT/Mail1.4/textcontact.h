#ifndef TEXTCONTACT_H
#define TEXTCONTACT_H

#include <QWidget>


namespace Ui {
class textContact;
}

class textContact : public QWidget
{
    Q_OBJECT

public:
    explicit textContact(QWidget *parent = 0);
    ~textContact();

private slots:
    void on_add_clicked();

    void on_quit_clicked();

private:
    Ui::textContact *ui;
};

#endif // TEXTCONTACT_H

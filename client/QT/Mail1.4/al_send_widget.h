#ifndef AL_SEND_WIDGET_H
#define AL_SEND_WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>


namespace Ui {
class al_send_Widget;
}

class al_send_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit al_send_Widget(QWidget *parent = 0);
    ~al_send_Widget();
    void al_send();

private:
    Ui::al_send_Widget *ui;


private slots:
    void ButtonRead_clicked();

signals:
    void check_btn_clicked(QString x);
};

#endif // AL_SEND_WIDGET_H

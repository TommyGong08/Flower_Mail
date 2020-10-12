#ifndef MAILWIDGET_H
#define MAILWIDGET_H

#include <QWidget>


class MailWidget : public QWidget
{
    Q_OBJECT

public:
    MailWidget(QWidget *parent = 0);
    ~MailWidget();
};

#endif // MAILWIDGET_H

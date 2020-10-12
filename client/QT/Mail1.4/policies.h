#ifndef POLICIES_H
#define POLICIES_H

#include <QWidget>


namespace Ui {
class Policies;
}

class Policies : public QWidget
{
    Q_OBJECT

public:
    explicit Policies(QWidget *parent = 0);
    ~Policies();

private:
    Ui::Policies *ui;
};

#endif // POLICIES_H

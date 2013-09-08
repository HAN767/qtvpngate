#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include <QPushButton>
#include <QPoint>

class MyPushButton: public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent =0);
    ~MyPushButton();
private slots:
    void slot_hasclicked();
signals:
    void sig_clieckButton(QPoint);
};



#endif // MYPUSHBUTTON_H

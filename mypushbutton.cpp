#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    :QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),SLOT(slot_hasclicked()));
}
MyPushButton::~MyPushButton()
{

}

void MyPushButton::slot_hasclicked()
{
    emit sig_clieckButton(this->pos());
}

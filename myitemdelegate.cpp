#include "myitemdelegate.h"
#include <QStandardItemModel>
#include <QPainter>
#include "mypushbutton.h"

MyItemDelegate::MyItemDelegate(QObject *parent)
    :QItemDelegate(parent)
{
    _state = QStyle::State_Enabled;
}

MyItemDelegate::~MyItemDelegate()
{

}

void MyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QStandardItemModel *model = static_cast<const QStandardItemModel*>(index.model());
    QStandardItem *item = model->item(index.row());
    QString text = item->text();
    QRect rect = option.rect;

    QRect textRect(rect);
    textRect.setHeight(30);
    painter->drawText(textRect,text);

    MyPushButton *btn = new MyPushButton;

}

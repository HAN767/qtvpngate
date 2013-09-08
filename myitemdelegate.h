#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H
#include <QItemDelegate>

class MyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    MyItemDelegate(QObject *parent = 0);
    ~MyItemDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;
//    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:
    void buttomClicked(const QModelIndex &index);
private:
    QStyle::State _state;
};

#endif // MYITEMDELEGATE_H

#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H
#include <QAbstractTableModel>

class MyTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = 0);
    ~MyTableModel();
protected:

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // MYTABLEMODEL_H

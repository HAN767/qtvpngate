#include "mytablemodel.h"

MyTableModel::MyTableModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}


MyTableModel::~MyTableModel()
{

}


int MyTableModel::rowCount(const QModelIndex &parent) const
{

}

int MyTableModel::columnCount(const QModelIndex &parent) const
{

}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{

}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

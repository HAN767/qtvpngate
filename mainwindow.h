#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytableview.h"
#include <QProcess>


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    MyTableView *m_serverlist;
    ~MainWindow();
private:
    QStandardItemModel *m_standmodel;
    QProcess *m_proc;
    QStringList m_ListEnv;
    void setHorizontalHeaderList(const QStringList &list);
    QList<QStandardItem*> appendRowToView(const QStringList &list);
private slots:
    void slot_ClieckItemRow(const QModelIndex);
    void slot_ReadyToConnectServer();
    void slot_readyReadStandardOutput();
};

#endif // MAINWINDOW_H

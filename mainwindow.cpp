#include "mainwindow.h"
#include <QDir>
#include <QApplication>
#include <QKeyEvent>

static QString openvpn_config  = QDir::homePath()+"/openvpn.cfg";
static QString openvpn_log  = QDir::homePath()+"/openvpn.log";
static QString openvpn_exec = "/usr/sbin/openvpn";



static QStringList view_header(QStringList() << "Connect Name" << "Status" << "VPN Server Host");
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_standmodel(new QStandardItemModel),
    m_serverlist(new MyTableView),
    m_proc(new QProcess)
{

    m_ListEnv = m_proc->systemEnvironment();
    QTableView *main_view = new QTableView;
    m_serverlist->hide();

    connect(m_proc,SIGNAL(readyReadStandardOutput()),SLOT(slot_readyReadStandardOutput()));

    connect(m_serverlist,SIGNAL(sig_readytoconnect()),SLOT(slot_ReadyToConnectServer()));
    connect(main_view,SIGNAL(clicked(QModelIndex)),SLOT(slot_ClieckItemRow(QModelIndex)));
    main_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    main_view->setSelectionMode(QAbstractItemView::SingleSelection);
    main_view->setGridStyle(Qt::NoPen);

    m_standmodel->appendRow(new QStandardItem("VPN Server List"));

    main_view->setModel(m_standmodel);
    setHorizontalHeaderList(view_header);

    QVBoxLayout *vLay = new QVBoxLayout;
    vLay->addWidget(main_view);

    QWidget *w = new QWidget;
    w->setLayout(vLay);
    setCentralWidget(w);
    this->setFixedSize(400,400);

}

void MainWindow::slot_ClieckItemRow(const QModelIndex index)
{
    const int row = index.row();
    if(row==0)
    {
        m_serverlist->show();
        return;
    }
}


void MainWindow::slot_ReadyToConnectServer()
{
    if(m_proc->state() == QProcess::Running)
    {
        m_proc->terminate();
        m_proc->kill();
        while(m_proc->waitForFinished());
    }


    m_proc->start(openvpn_exec,QStringList() /*<< "--user" << m_ListEnv.at(20).section("=",1,1) */<< "--config" << openvpn_config
                  << "--log" <<openvpn_log << "--status" << "openvpn.status" << "1");
    QStringList tlist = m_serverlist->getCurrentList();
//    m_standmodel->appendRow(appendRowToView(QStringList() << tlist.at(0) << "connectting" << tlist.at(1)));
}

QList<QStandardItem*> MainWindow::appendRowToView(const QStringList &list)
{
    QList<QStandardItem*> rowlist;
    for(int i = 0 ; i < list.count();i++)
    {
        rowlist.append(new QStandardItem(list.at(i)));
    }
    return rowlist;
}


void MainWindow::slot_readyReadStandardOutput()
{
    QString tmp = m_proc->readAll();

}

void MainWindow::setHorizontalHeaderList(const QStringList &list)
{
    for(int i = 0 ; i < list.count();i++)
    {
        m_standmodel->setHorizontalHeaderItem(i,new QStandardItem(list.at(i)));
    }


}


MainWindow::~MainWindow()
{

}




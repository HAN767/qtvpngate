#include "mytableview.h"
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>


static QString openvpn_config  = QDir::homePath()+"/openvpn.cfg";
static QStringList headItems(QStringList() << "Service Name"
                             << "IP" << "Score" << "ping" << "Speed"
                             << "CountryLong" << "CountryShort"
                             << "NumVpnSessions" << "Uptime" << "TotalUser"
                             << "TotalTrafic" << "LogType" << "Operator"
                             << "Message" /*<< "OpenVpn"*/);

static int oneK = 1024;
static int oneM = oneK*oneK;

MyTableView::MyTableView(QWidget *parent)
    :QWidget(parent),
      m_Layout(new QGridLayout),
      m_csvLine(new QLineEdit),
      m_OpenCsvFile(new QPushButton("open")),
      m_standModel(new QStandardItemModel)
{
    this->setWindowFlags(Qt::WindowMaximizeButtonHint|
                         Qt::WindowCloseButtonHint);
    connect(m_OpenCsvFile,SIGNAL(clicked()),SLOT(slot_openCSVFile()));
    ServerView = new QTableView;

    m_csvLine->setEnabled(false);

    connect(ServerView,SIGNAL(clicked(QModelIndex)),SLOT(slot_ClickedItem(QModelIndex)));
    ServerView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ServerView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ServerView->setSelectionMode(QAbstractItemView::SingleSelection);
    setHorizontalHeaderList(headItems);
    ServerView->setModel(m_standModel);
    m_Layout->addWidget(m_csvLine,0,0);
    m_Layout->addWidget(m_OpenCsvFile,0,1);
    m_Layout->addWidget(ServerView,1,0,1,2);
    setLayout(m_Layout);
    this->setFixedSize(800,400);
    this->setFocus();
}


QStringList MyTableView::getCurrentList() const
{
    return m_currentStringList;
}

void MyTableView::slot_ClickedItem(const QModelIndex &index)
{
    QFile fd(openvpn_config);
    if(!fd.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    fd.write(QByteArray::fromBase64(m_listbase64.at(index.row()).toLocal8Bit()));
    fd.close();
    this->hide();
    m_currentStringList = m_standModel->data(index).toStringList();
    emit sig_readytoconnect();
}

MyTableView::~MyTableView()
{

}

void MyTableView::slot_openCSVFile()
{
//    QFile fd(QFileInfo(m_configfile).absolutePath()+"/lastopen");
//    if(fd.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        m_LastPath =fd.readLine().trimmed();
//        fd.close();
//    }

//    if(m_LastPath.isEmpty())
//    m_LastPath = QFileInfo(m_configfile).absolutePath();
//    QString s_format("支持的格式 (");
//    int i =0;
//    while(QString(QByteArray(support_format[i])).compare("end"))
//    {
//        s_format.append("*.");
//        s_format.append(support_format[i]);
//        s_format.append(" ");
//        i++;
//    }
//    s_format.replace(s_format.length(),1,")");
    QString m_LastPath("");
    m_csvfile =  QFileDialog::getOpenFileName(this,tr("选择文件"),m_csvLine->text(),
                                                          tr("support csv (*.csv *.txt *.html)"));

//    if(listfiles.count() >0)
//    {
//        m_LastPath = QFileInfo(listfiles.at(0)).absolutePath();

//        if(fd.open(QIODevice::WriteOnly|QIODevice::Text))
//        {
//            QTextStream ts(&fd);
//            ts.setAutoDetectUnicode(false);
//            ts.setGenerateByteOrderMark(true);
//            ts.setCodec("UTF-8");
//            ts << m_LastPath;
//            fd.close();
//        }

//    }


//    if(listfiles.isEmpty())
//        return ;
//    slot_GotFileListFromGuide(listfiles);

    if(m_csvfile.isEmpty())
        return;

    m_csvLine->setText(m_csvfile);


    QFile fd(m_csvfile);
    if(!fd.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    if(!fd.readLine().startsWith("*vpn_servers"))
    {
        QMessageBox::warning(this,"error","wrong file format!");
        fd.close();
        return;
    }
    while(!fd.atEnd())
    {
        QString line = fd.readLine();
        if(line.startsWith("#") ||
                line.startsWith("*"))
                continue;
        m_standModel->appendRow(appendRowFromList(line.split(",")));
    }
    fd.close();
}


QList<QStandardItem*> MyTableView::appendRowFromList(const QStringList &list)
{
    QList<QStandardItem*> rowlist;
    for(int i = 0 ; i < list.count()-1;i++)
    {

        switch(i)
        {
        case 4:
            rowlist.append(new QStandardItem(ConvertNumberToMBps(list.at(i))));
            continue;
        case 8:
            rowlist.append(new QStandardItem(ConvertNumberToStringTime(list.at(i))));
            continue;
        }

        rowlist.append(new QStandardItem(list.at(i)));
    }

    m_listbase64.append(list.last());
    return rowlist;
}


QString MyTableView::ConvertNumberToMBps(const QString &num)
{
    long speed = num.toLong();
    QString tmp;
    if(speed > oneM)
    {

        speed = speed / oneM;
        tmp = (QString::number(speed)+" Mbps");
        return tmp;
    }
    else
    {
        speed = speed / oneK;
        tmp = (QString::number(speed)+" Kbps");
        tmp;
    }

}

QString MyTableView::ConvertNumberToStringTime(const QString &num)
{
    long duration = num.toLong();
//    QTime t(0,0,0);
//    t = t.addMSecs(8117991);
//    return t.toString("hh:mm:ss");
    return QDateTime::fromTime_t(duration).toString("dd天hh小时mm分钟");

}

void MyTableView::setHorizontalHeaderList(const QStringList &list)
{
    for(int i = 0 ; i < list.count();i++)
    {
        m_standModel->setHorizontalHeaderItem(i,new QStandardItem(list.at(i)));
    }


}

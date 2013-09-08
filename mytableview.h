#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QGridLayout>
#include "mypushbutton.h"
#include <QLineEdit>


class MyTableView: public QWidget
{
    Q_OBJECT
public:
    explicit MyTableView(QWidget *parent=0);
    ~MyTableView();
    QStringList getCurrentList() const;
    QTableView *ServerView;
private:
    QGridLayout *m_Layout;
    QLineEdit* m_csvLine;
    QPushButton *m_OpenCsvFile;
    MyPushButton *m_btn_connect;
    QString m_csvfile;
    QStandardItemModel* m_standModel;

    QStringList m_listbase64;
    QStringList m_currentStringList;


    void setHorizontalHeaderList(const QStringList &list);
    QList<QStandardItem*> appendRowFromList(const QStringList &list);

    QString ConvertNumberToStringTime(const QString &);
    QString ConvertNumberToMBps(const QString &);
private slots:
    void slot_openCSVFile();
    void slot_ClickedItem(const QModelIndex & );
signals:
    void sig_readytoconnect();

};

#endif // MYTABLEVIEW_H

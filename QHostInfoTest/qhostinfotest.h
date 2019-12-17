#ifndef QHOSTINFOTEST_H
#define QHOSTINFOTEST_H

#include <QMainWindow>
#include <QHostInfo>

namespace Ui {
class QHostInfoTest;
}

class QHostInfoTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit QHostInfoTest(QWidget *parent = 0);
    ~QHostInfoTest();


private:
    void DebugOutput(const QString &msg);

    // 获取本地主机名字
    void Test_localHostName();

    // 返回主机名字的IP地址
    void Test_fromName();

    // 异步查询主机IP地址，返回一个查询ID
    void Test_lookupHost(QString host_name = "www.bing.com");
    private slots: void lookedupHostInfo(const QHostInfo &host_info);

private:
    Ui::QHostInfoTest *ui;

private slots:
    void on_pushButtonGetLocalHostName_clicked();

    void on_pushButtonGetHostAddress_clicked();

    void on_pushButtonLookupHost_clicked();
};

#endif // QHOSTINFOTEST_H

#include "qhostinfotest.h"
#include "ui_qhostinfotest.h"

QHostInfoTest::QHostInfoTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QHostInfoTest)
{
    ui->setupUi(this);
}

QHostInfoTest::~QHostInfoTest()
{
    delete ui;
}

void QHostInfoTest::DebugOutput(const QString &msg)
{
    qDebug() << msg;
    ui->plainTextEditOutput->appendPlainText(msg);
}

void QHostInfoTest::Test_localHostName()
{
    QString host_name = QHostInfo::localHostName();

    this->DebugOutput(host_name);
}

void QHostInfoTest::Test_fromName()
{
    QHostInfo host_info = QHostInfo::fromName(QHostInfo::localHostName());

    QList<QHostAddress> address_list = host_info.addresses();

    for (int i = 0; i < address_list.count(); i++)
    {
        QHostAddress host_address = address_list.at(i);

        QAbstractSocket::NetworkLayerProtocol proto = host_address.protocol();

        if (proto == QAbstractSocket::IPv4Protocol)
        {
            QString ip = host_address.toString();

            this->DebugOutput("local IPV4: " + ip);
        }
    }
}

void QHostInfoTest::Test_lookupHost(QString host_name)
{
    QHostInfo::lookupHost(host_name, this, SLOT(lookedupHostInfo(QHostInfo)));
}

void QHostInfoTest::lookedupHostInfo(const QHostInfo &host_info)
{
    if (host_info.error() != QHostInfo::NoError)
    {
        QString err_msg = "lookedupHostInfo failed, error msg: " + host_info.errorString();

        this->DebugOutput(err_msg);

        return;
    }

    QList<QHostAddress> address_list = host_info.addresses();

    for (int i = 0; i < address_list.count(); i++)
    {
        QHostAddress host_address = address_list.at(i);

        QAbstractSocket::NetworkLayerProtocol proto = host_address.protocol();

        if (proto == QAbstractSocket::IPv4Protocol)
        {
            QString ip = host_address.toString();

            this->DebugOutput("lookup IPV4: " + ip);
        }
    }
}

void QHostInfoTest::on_pushButtonGetLocalHostName_clicked()
{
    this->Test_localHostName();
}

void QHostInfoTest::on_pushButtonGetHostAddress_clicked()
{
    this->Test_fromName();
}

void QHostInfoTest::on_pushButtonLookupHost_clicked()
{
    this->Test_lookupHost();
}

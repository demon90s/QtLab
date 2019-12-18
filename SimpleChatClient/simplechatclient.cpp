#include "simplechatclient.h"
#include "ui_simplechatclient.h"

#include <QHostAddress>

SimpleChatClient::SimpleChatClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleChatClient),
    m_socket(NULL)
{
    ui->setupUi(this);

    m_socket = new QTcpSocket;

    connect(m_socket, SIGNAL(connected()), this, SLOT(OnConnected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(OnDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
}

SimpleChatClient::~SimpleChatClient()
{
    delete ui;
    ui = NULL;

    delete m_socket;
}

void SimpleChatClient::DebugOutput(const QString &msg)
{
    if (ui == NULL)
    {
        return;
    }

    qDebug() << msg;
    ui->plainTextEditOutput->appendPlainText(msg);
}

void SimpleChatClient::Connect(const QString &ip, quint16 port)
{
    if (m_socket->isValid())
    {
        return;
    }

    QHostAddress host_address(ip);

    m_socket->connectToHost(host_address, port);
}

void SimpleChatClient::Disconnect()
{
    m_socket->close();
}

void SimpleChatClient::SendMsg(const QByteArray &msg)
{
    m_socket->write(msg);
}

void SimpleChatClient::OnConnected()
{
    QString server_ip = m_socket->peerAddress().toString();
    quint16 server_port = m_socket->peerPort();

    {
        QString msg = "Connected to server: ";
        msg += server_ip;
        msg += ":";
        msg += QString::number(server_port);
        this->DebugOutput(msg);
    }
}

void SimpleChatClient::OnDisconnected()
{
    QString server_ip = m_socket->peerAddress().toString();
    quint16 server_port = m_socket->peerPort();

    {
        QString msg = "Disconnected from server: ";
        msg += server_ip;
        msg += ":";
        msg += QString::number(server_port);
        this->DebugOutput(msg);
    }
}

void SimpleChatClient::OnReadyRead()
{
    if (m_socket->canReadLine())
    {
        QByteArray msg = m_socket->readLine();

        this->DebugOutput(msg);
    }
}

void SimpleChatClient::on_pushButtonSend_clicked()
{
    // 基于行的协议
    QString msg = ui->lineEditMsg->text();
    if (msg.isEmpty())
    {
        return;
    }

    msg += '\n';

    this->SendMsg(msg.toUtf8());

    ui->lineEditMsg->clear();
}

void SimpleChatClient::on_pushButtonDisconnect_clicked()
{
    this->Disconnect();
}

void SimpleChatClient::on_pushButtonConnect_clicked()
{
    QString ip = ui->lineEditServerIP->text();
    quint16 port = ui->spinBoxServerPort->value();

    this->Connect(ip, port);
}

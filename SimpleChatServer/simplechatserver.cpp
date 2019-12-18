#include "simplechatserver.h"
#include "ui_simplechatserver.h"

SimpleChatServer::SimpleChatServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimpleChatServer)
{
    ui->setupUi(this);

    connect(&m_tcp_server, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}

SimpleChatServer::~SimpleChatServer()
{
    delete ui;
    ui = NULL;
}

void SimpleChatServer::DebugOutput(const QString &msg)
{
    if (ui == NULL)
    {
        return;
    }

    qDebug() << msg;
    ui->plainTextEditOutput->appendPlainText(msg);
}

void SimpleChatServer::StartListen(const QHostAddress ip, quint16 port)
{
    if (!m_tcp_server.listen(ip, port))
    {
        this->DebugOutput("Listen failed");
        return;
    }

    QString listen_ip = m_tcp_server.serverAddress().toString();
    quint16 listen_port = m_tcp_server.serverPort();

    {
        QString msg = "Listen on: ";
        msg += listen_ip;
        msg += ":";
        msg += QString::number(listen_port);
        this->DebugOutput(msg);
    }
}

void SimpleChatServer::StopListen()
{
    if (m_tcp_server.isListening())
    {
        m_tcp_server.close();

        this->DebugOutput("Stop Listening");
    }
}

void SimpleChatServer::OnClientConnected(QTcpSocket *client_socket)
{
    QString client_ip = client_socket->peerAddress().toString();
    quint16 client_port = client_socket->peerPort();

    {
        QString msg = "Connect a clien from: ";
        msg += client_ip;
        msg += ":";
        msg += QString::number(client_port);
        this->DebugOutput(msg);
    }
}

void SimpleChatServer::OnNewConnection()
{
    QTcpSocket *client_socket = m_tcp_server.nextPendingConnection();
    m_client_sockets.insert(client_socket);

    connect(client_socket, SIGNAL(disconnected()), this, SLOT(OnClientDisconnect()));
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(OnSocketReadyRead()));

    this->OnClientConnected(client_socket);
}

void SimpleChatServer::OnClientDisconnect()
{
    QTcpSocket *client_socket = static_cast<QTcpSocket *>(sender());

    QString client_ip = client_socket->peerAddress().toString();
    quint16 client_port = client_socket->peerPort();

    client_socket->deleteLater();
    m_client_sockets.remove(client_socket);

    {
        QString msg = "A clien disconnect from: ";
        msg += client_ip;
        msg += ":";
        msg += QString::number(client_port);
        this->DebugOutput(msg);
    }
}

void SimpleChatServer::OnSocketReadyRead()
{
    // 基于文本行通信
    QTcpSocket *client_socket = static_cast<QTcpSocket *>(sender());

    while (client_socket->canReadLine())
    {
        QString client_ip = client_socket->peerAddress().toString();
        quint16 client_port = client_socket->peerPort();

        QByteArray line = client_socket->readLine();

        QString msg;
        msg += client_ip;
        msg += ":";
        msg += QString::number(client_port);
        msg += " says: ";
        msg += line;

        // 广播给其它客户端
        for (auto it = m_client_sockets.begin(); it != m_client_sockets.end(); ++it)
        {
            (*it)->write(msg.toUtf8());
        }

        this->DebugOutput(msg);
    }
}

void SimpleChatServer::on_pushButtonStartListen_clicked()
{
    QHostAddress ip("127.0.0.1");
    quint16 port = ui->spinBoxListenPort->value();

    this->StartListen(ip, port);
}

void SimpleChatServer::on_pushButtonStopListen_clicked()
{
    this->StopListen();
}

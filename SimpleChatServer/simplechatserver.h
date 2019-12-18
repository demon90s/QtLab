#ifndef SIMPLECHATSERVER_H
#define SIMPLECHATSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>

namespace Ui {
class SimpleChatServer;
}

class SimpleChatServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleChatServer(QWidget *parent = 0);
    ~SimpleChatServer();

private slots:
    void on_pushButtonStartListen_clicked();

    void on_pushButtonStopListen_clicked();

private:
    void DebugOutput(const QString &msg);

    void StartListen(const QHostAddress ip, quint16 port);
    void StopListen();

    void OnClientConnected(QTcpSocket *client_socket);

private:
    Ui::SimpleChatServer *ui;

    QTcpServer m_tcp_server;
    QSet<QTcpSocket *> m_client_sockets;

private slots:
    void OnNewConnection();
    void OnClientDisconnect();
    void OnSocketReadyRead();
};

#endif // SIMPLECHATSERVER_H

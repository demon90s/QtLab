#ifndef SIMPLECHATCLIENT_H
#define SIMPLECHATCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class SimpleChatClient;
}

class SimpleChatClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimpleChatClient(QWidget *parent = 0);
    ~SimpleChatClient();

private:
    void DebugOutput(const QString &msg);

    void Connect(const QString &ip, quint16 port);
    void Disconnect();
    void SendMsg(const QByteArray &msg);

private:
    Ui::SimpleChatClient *ui;

    QTcpSocket *m_socket;

private slots:
    void OnConnected();
    void OnDisconnected();
    void OnReadyRead();

    void on_pushButtonSend_clicked();
    void on_pushButtonDisconnect_clicked();
    void on_pushButtonConnect_clicked();
};

#endif // SIMPLECHATCLIENT_H

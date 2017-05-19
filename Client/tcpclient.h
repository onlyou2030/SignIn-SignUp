#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QMessageBox>

namespace Ui {
class TcpClient;
}

class TcpClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();

protected:
    void init();
    void connectServer();

private slots:
    void on_sendBtn_clicked();

    void displayError(QAbstractSocket::SocketError);

    void on_signBtn_clicked();

    void readMessages();

private:
    Ui::TcpClient *ui;
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIENT_H

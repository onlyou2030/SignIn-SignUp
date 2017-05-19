#include "tcpclient.h"
#include "ui_tcpclient.h"

#define ip "192.168.1.165"
#define port 8000

TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    ui->passwardLineEdit->setEchoMode(QLineEdit::Password);  //密码方式显示文本
    init();
    connectServer();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::init()
{
    tcpSocket=new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

void TcpClient::connectServer()
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(ip,port);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

void TcpClient::on_sendBtn_clicked()
{
    QString userName=ui->userLineEdit->text();
    QString passward=ui->passwardLineEdit->text();
    if(userName=="" || passward=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString bs="b";
    QString data=bs+"#"+userName+"#"+passward;
    tcpSocket->write(data.toLatin1());
}


void TcpClient::on_signBtn_clicked()
{
    QString userName=ui->userLineEdit->text();
    QString passward=ui->passwardLineEdit->text();
    if(userName=="" || passward=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString as="a";
    QString data=as+"#"+userName+"#"+passward;
    tcpSocket->write(data.toLatin1());
}


void TcpClient::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}


void TcpClient::readMessages()
{
    QString data=tcpSocket->readAll();
    QStringList list=data.split("#");
    if(list[0]=="a" && list[1]=="true")
        QMessageBox::information(this,"信息提示","注册成功!",QMessageBox::Ok);
    else if(list[0]=="a" && list[1]=="false")
        QMessageBox::information(this,"信息提示","注册失败,用户名已经被注册!",QMessageBox::Ok);
    else if(list[0]=="b" && list[1]=="true")
        QMessageBox::information(this,"信息提示","登录成功!",QMessageBox::Ok);
    else if(list[0]=="b" && list[1]=="false")
            QMessageBox::information(this,"信息提示","登录失败,用户名或密码错误!",QMessageBox::Ok);
    else
        return;
}

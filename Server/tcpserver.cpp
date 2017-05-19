#include "tcpserver.h"
#include "ui_tcpserver.h"
#include "mysql.h"

TcpServer::TcpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    init();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::init()
{
    this->tcpServer=new QTcpServer(this);
    this->tcpSocket=new QTcpSocket(this);

    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}


void TcpServer::receiveData()
{
    QString data=tcpSocket->readAll();
    QStringList list=data.split("#");
    bool ret=0;
    if(list[0]=="a")     //注册
        ret=checkSignUp(list[1],list[2]);
    else if(list[0]=="b")  //登录
        ret=checkSignIn(list[1],list[2]);
    else
        return;
    QString sendData=list[0];
    if(ret)
        sendData+="#true";
    else
        sendData+="#false";
    tcpSocket->write(sendData.toLatin1());
}

void TcpServer::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::Any,8000))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
}


void TcpServer::acceptConnection()
{
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));   //**********
}

void TcpServer::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}

bool TcpServer::checkSignIn(QString name,QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->loguser(name,passward);
    return ret;
}

bool TcpServer::checkSignUp(QString name, QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->signup(name,passward);
    return ret;
}

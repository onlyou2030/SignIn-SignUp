#include "mysql.h"

MySql::MySql()
{

}

void MySql::initsql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("!@#123");
    db.setDatabaseName("User");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            createtable();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
}

void MySql::createtable()
{
    query=new QSqlQuery;

    query->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(30))");

    /*创建root用户*/
    query->exec("insert into user value('root', 'root')");
}


bool MySql::loguser(QString name, QString passward)
{
    QString str=QString("select * from user where name='%1' and passward='%2'").arg(name).arg(passward);
    query=new QSqlQuery;
    query->exec(str);
    query->last();
    int record=query->at()+1;
    if(record==0)
        return false;
    return true;
}


bool MySql::signup(QString name,QString passward)
{
    QString str=QString("select * from user where name='%1").arg(name);
    query=new QSqlQuery;
    query->exec(str);
    query->last();
    int record=query->at()+1;
    if(record!=0)
        return false;
    str=QString("insert into user value('%1','%2')").arg(name).arg(passward);
    bool ret=query->exec(str);
    return ret;
}

#include "mydatabasemodule.h"

#include <QDebug>
#include <QFileInfo>
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <tuple>

MyDataBaseModule::MyDataBaseModule(QWidget *parent) : QWidget(parent)
{
    m_sUserName = "root";
    m_sPasswd = "111111";
}

MyDataBaseModule::~MyDataBaseModule(){
    m_oDatabase.close();
}

void MyDataBaseModule::connect2UserDataBase(const QString& userName, const QString& passwd){
    m_sUserName = userName;
    m_sPasswd = passwd;

    QDir dir;
    QString currentPath = "../user";
    qDebug() << "current path: " << currentPath;
    if(!dir.exists(currentPath))
        qDebug() << dir.mkdir(currentPath);

    m_sDataBasePath = currentPath + "/" + m_sUserName + ".db";
    qDebug() << "DataBasePath" << m_sDataBasePath;

    m_oDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_oDatabase.setDatabaseName(m_sDataBasePath);
    m_oDatabase.setUserName(m_sUserName);
    m_oDatabase.setPassword(m_sPasswd);
    m_oDatabase.open();

    if(m_oDatabase.isOpen())
        qDebug() << "数据库打开成功";
    else
        qFatal("数据库打开失败");

}

bool MyDataBaseModule::isTableExist(const QString& tableName){
    QSqlQuery query(m_oDatabase);
    query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg(tableName));
    query.exec();
    query.next();
    return query.value(0).toBool();
}

void MyDataBaseModule::createTable(const QString &tableName){
    if(isTableExist(tableName)){
        qDebug() << "该表已存在";
    }
    else{
        QSqlQuery query(m_oDatabase);
        qDebug() << "准备创建表: "<< tableName;
        QString sqlCmd = "CREATE TABLE " + tableName + " (id INTEGER PRIMARY KEY AUTOINCREMENT, SongName VARCHAR, Author VARCHAR, SongLink VARCHAR, CoverLink VARCHAR)";
        query.prepare(sqlCmd);

        if(query.exec())
            qDebug() << "创建表成功";
        else
            qFatal("创建表失败");
    }
}

void MyDataBaseModule::deleteOldRecords(){

}

bool MyDataBaseModule::insertRecord(const QString& tableName, const QVector<QString>& record){
    QSqlQuery query(m_oDatabase);
    QString sql_cmd = "SELECT count(*) FROM " + tableName + " WHERE SongName=?;";
    qDebug() << sql_cmd << record[0];
    query.prepare(sql_cmd);
    query.addBindValue(record[0]);
    query.exec();
    query.next();
    qDebug() << query.value(0);
    if(!query.value(0).toBool()){
        QString sql_cmd = "INSERT OR IGNORE INTO " + tableName + " (SongName, Author, SongLink, CoverLink) VALUES (?, ?, ?, ?)";

        query.prepare(sql_cmd);
        for(const QString& item: record)
            query.addBindValue(item);
        if(query.exec())
            qDebug() << "成功插入一条记录";
        else
            qDebug() << "插入记录失败";

        return true;
    }
    else{
        qDebug() << "记录已经存在，不执行插入";
        return false;
    }
}

void MyDataBaseModule::insertRecords(const QString& tableName, const QVector<QVector<QString>>& records){
    QSqlQuery query;
    QString sql_cmd = "INSERT OR IGNORE INTO " + tableName + " (SongName, Author, SongLink, CoverLink) VALUES (?, ?, ?, ?)";

    for(const QVector<QString>& record: records){
        query.prepare(sql_cmd);
        for(const QString& item: record){
            query.addBindValue(item);
        }
        if(query.exec())
            qDebug() << "成功插入一条记录";
        else
            qDebug() << "插入记录失败";
    }
}

QSqlRecord MyDataBaseModule::fetchRecords(const QString& tableName, const QString& key){
    QSqlQuery query(m_oDatabase);
    QString sqlcmd = "SELECT SongLink, CoverLink FROM " + tableName + " WHERE SongName=? or Author=?;";
    query.prepare(sqlcmd);
    query.addBindValue(key);
    query.addBindValue(key);

   if(query.exec())
       qDebug() << "查询记录成功";
   else
       qFatal("查询记录失败");

    return query.record();
}

QVector<std::tuple<QString,QString,QString,QString>> MyDataBaseModule::fetchRecords(const QString& tableName){
    if(!isTableExist(tableName))
        return {};

    QSqlQuery query(m_oDatabase);
    QString sqlcmd = "SELECT SongName, Author, SongLink, CoverLink FROM " + tableName + ";";
    query.prepare(sqlcmd);

    if(query.exec())
        qDebug() << "查询记录成功";
    else
        qFatal("查询记录失败");
    QVector<std::tuple<QString,QString,QString,QString>> records;
    while(query.next()){
        std::tuple<QString,QString,QString,QString> record(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString());
        records.push_back(record);
    }
    return records;
}

void MyDataBaseModule::deleteTable(const QString& tableName){
    if(isTableExist(tableName)){
        QSqlQuery query(m_oDatabase);
        QString sqlcmd = "DROP TABLE " + tableName + ";";
        query.prepare(sqlcmd);
        if(query.exec())
            qDebug() << "删除表成功";
        else
            qFatal("删除表失败");
    }
    else
        qDebug() << "该表不存在，不可删除";
}

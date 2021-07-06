#ifndef MYDATABASEMODULE_H
#define MYDATABASEMODULE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVector>
#include <tuple>

class MyDataBaseModule : public QWidget
{
    Q_OBJECT
public:
    explicit MyDataBaseModule(QWidget *parent = nullptr);
    ~MyDataBaseModule();

    void connect2UserDataBase(const QString& username, const QString& passwd);
    void deleteOldRecords();
    bool insertRecord(const QString& tableName, const QVector<QString>& record);
    void insertRecords(const QString& tableName, const QVector<QVector<QString>>& records);
    QSqlRecord fetchRecords(const QString& tableName, const QString& key);
    QVector<std::tuple<QString, QString, QString, QString>> fetchRecords(const QString& tableName);
    void deleteTable(const QString& tableName);
    void createTable(const QString& tableName);

    bool isTableExist(const QString& tableName);

signals:

private:
    QSqlDatabase m_oDatabase;
    QString m_sUserName;
    QString m_sPasswd;
    QString m_sDataBasePath;
};

#endif // SONGSEARCH_H

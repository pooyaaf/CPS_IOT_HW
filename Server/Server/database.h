#ifndef DATABASE_H
#define DATABASE_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Database
{
public:
    Database();
    void addLogInTime(const QString username);
    QString getLogs();
    bool isValid(QString rfid);

private:
    QJsonArray data;
    QJsonArray members;
};

#endif // DATABASE_H

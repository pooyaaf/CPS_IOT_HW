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
    void addLogInTime(const QString rfid);
    QString getLogs();
    QJsonObject getLastLog();
    bool isValid(QString rfid);

private:
    QString getUsername(const QString &rfid);

    QJsonArray data;
    QJsonArray members;
};

#endif // DATABASE_H

#ifndef DATABASE_H
#define DATABASE_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Database
{
public:
    void addLogInTime(const QString username);
    QString getLogs();

private:
    QJsonArray data;
};

#endif // DATABASE_H

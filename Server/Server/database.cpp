#include "database.h"
QT_USE_NAMESPACE

void Database::addLogInTime(const QString username)
{
    auto currentTime = QDateTime::currentDateTime();
    QJsonObject log;
    log["date"] = currentTime.toString("MM/dd/yyyy");
    log["time"] = currentTime.toString("hh:mm");
    log["username"] = username;
    data.append(log);
}

QString Database::getLogs()
{
    QJsonDocument doc(data);
    return doc.toJson();
}

#include "database.h"
QT_USE_NAMESPACE

Database::Database()
{
    for (int i = 0; i < 10; ++i) {
        QJsonObject member;
        member["username"] = "ali" + QString::number(i);
        member["rfid"] = "123456789" + QString::number(i);
        members.append(member);
    }
}

QString Database::getUsername(const QString &rfid)
{
    for (int i = 0; i < members.size(); i++)
        if (members.at(i)["rfid"] == rfid)
            return members.at(i)["username"].toString();
    return QString();
}

bool Database::isValid(QString rfid)
{
    return getUsername(rfid) != "";
}

void Database::addLogInTime(const QString rfid)
{
    auto currentTime = QDateTime::currentDateTime();
    auto userName = getUsername(rfid);
    if (userName == "")
        userName = "Not Found!";

    QJsonObject log;
    log["date"] = currentTime.toString("MM/dd/yyyy");
    log["time"] = currentTime.toString("hh:mm");
    log["username"] = userName;
    data.append(log);
}

QJsonObject Database::getLastLog()
{
    return data.last().toObject();
}

QString Database::getLogs()
{
    QJsonDocument doc(data);
    return doc.toJson();
}

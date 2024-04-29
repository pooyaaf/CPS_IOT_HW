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

bool Database::isValid(QString rfid)
{
    for (int i = 0; i < members.size(); i++)
        if (members.at(i)["rfid"] == rfid)
            return true;

    return false;
}

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

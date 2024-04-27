#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include <QJsonArray>
#include <QJsonDocument>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public Q_SLOTS:
    void connectToServer(const QString &address, const QString &username, const QString &password);
    QJsonArray getHistory();

Q_SIGNALS:
    void connectionChanged(bool enabled);
    void newUser(const QString &username, const QString &date, const QString &time);
    void onHistoryUpdated(QJsonArray data);

private Q_SLOTS:
    void closed();
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    bool m_debug;
    QString username, password;
    QJsonArray cachedData;
};
#endif // CLIENT_H

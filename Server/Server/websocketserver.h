#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QtWebSockets>
#include "database.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(Database *database, quint16 port, bool debug = false, QObject *parent = nullptr);
    ~WebsocketServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    Database *database;
    inline static const QString USERNAME = "admin", PASSWORD = "admin";
};

#endif // SERVER_H

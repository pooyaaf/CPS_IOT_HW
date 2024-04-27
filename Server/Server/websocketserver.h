#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = nullptr);
    ~WebSocketServer();

private slots:
    void onNewConnection();
    void processTextMessage(const QString &message);
    void socketDisconnected();

private:
    QWebSocketServer *server;
};

#endif // SERVER_H

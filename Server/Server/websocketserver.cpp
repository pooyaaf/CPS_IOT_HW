#include "websocketserver.h"
#include <QDebug>

WebSocketServer::WebSocketServer(QObject *parent)
    : QObject(parent)
{
    server = new QWebSocketServer(QStringLiteral("RFID Server"),
                                  QWebSocketServer::NonSecureMode,
                                  this);
    if (!server->listen(QHostAddress::Any, 1234)) {
        qFatal("Failed to bind to port %d", 1234);
    }
    connect(server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

WebSocketServer::~WebSocketServer()
{
    server->close();
}

void WebSocketServer::onNewConnection()
{
    QWebSocket *socket = server->nextPendingConnection();
    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);
}

void WebSocketServer::processTextMessage(const QString &message)
{
    qDebug() << "Received message:" << message;
    // Process the received RFID value here
}

void WebSocketServer::socketDisconnected()
{
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        socket->deleteLater();
    }
}

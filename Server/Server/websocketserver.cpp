#include "websocketserver.h"
#include <QException>
#include <QtCore/QDebug>
#include "database.h"

QT_USE_NAMESPACE

Server::Server(Database *database, quint16 port, bool debug, QObject *parent)
    : QObject(parent)
    , m_pWebSocketServer(
          new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this))
    , m_debug(debug)
    , database(database)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Server listening on port" << port;
        connect(m_pWebSocketServer,
                &QWebSocketServer::newConnection,
                this,
                &Server::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &Server::closed);
    }
}

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << pSocket;
}

void Server::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;

    if (pClient) {
        auto recvd_mesg = message.split("|");
        if (recvd_mesg[0] == "login") {
            auto is_valid = recvd_mesg[1] == USERNAME && recvd_mesg[2] == PASSWORD;
            pClient->sendTextMessage(is_valid ? "login|ok" : "login|no");
        } else if (recvd_mesg[0] == "log") {
            qDebug() << database->getLogs();
            pClient->sendTextMessage("log|" + database->getLogs());
        } else {
            qDebug() << "not handle exception!";
            throw new QException();
        }
    }
}

void Server::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

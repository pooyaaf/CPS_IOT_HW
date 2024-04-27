#include "webserver.h"
#include <QTcpServer>
#include "clientconnection.h"
WebServer::WebServer(QObject *parent):
    QObject(parent),
    m_server(std::make_unique<QTcpServer>())
{
    connect(m_server.get(), &QTcpServer::newConnection,this,&WebServer::newConnection);
}

WebServer::~WebServer() = default;

void WebServer::start()
{
    m_server->listen(QHostAddress::Any, 80);
}

void WebServer::newConnection()
{
    const auto socket = m_server->nextPendingConnection();
    if(!socket)
        return;
    new ClientConnection(socket);
}

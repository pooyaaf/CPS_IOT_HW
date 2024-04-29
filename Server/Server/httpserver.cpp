#include "httpserver.h"

HttpServer::HttpServer(Database *database, QObject *parent)
    : QObject{parent}
    , database(database)
{
    QHttpServer httpServer;
    httpServer.route("/enter_door", [this](const QHttpServerRequest &request) {
        auto rfid = QString::fromUtf8(request.value("rfid").simplified().toStdString());
        return this->database->isValid(rfid) ? "ok" : "no";
    });

    httpServer.afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Server", "Qt HTTP Server");
        return std::move(resp);
    });

    const auto port = httpServer.listen(QHostAddress::Any);
    if (!port) {
        qWarning() << "QHttpServerExample Server failed to listen on a port.";
    }
}

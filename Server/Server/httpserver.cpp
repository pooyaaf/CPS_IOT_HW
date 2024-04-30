#include "httpserver.h"

HttpServer::HttpServer(Database *database, QObject *parent)
    : QObject{parent}
    , database(database)
{
    QHttpServer *httpServer = new QHttpServer();
    httpServer->route("/enter_door", [this](const QHttpServerRequest &request) {
        auto req = request.query().queryItems().at(0);
        if (req.first == "rfid") {
            auto rfid = req.second;
            qDebug() << "rcvd: " + rfid;
            auto time = QDateTime::currentDateTime().toString("hh:mm");
            return time + (this->database->isValid(rfid) ? "ok" : "no");
        }

        return QString("no");
    });

    httpServer->afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Server", "Qt HTTP Server");
        return std::move(resp);
    });

    const auto port = httpServer->listen(QHostAddress::Any, 80);
    if (!port) {
        qWarning() << "QHttpServerExample Server failed to listen on a port.";
    } else {
        qDebug() << "http server listening on " << port;
    }
}

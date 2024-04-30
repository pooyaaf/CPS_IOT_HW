#include "httpserver.h"

HttpServer::HttpServer(Database *database, QObject *parent)
    : QObject{parent}
    , database(database)
{
    QHttpServer *httpServer = new QHttpServer();
    httpServer->route("/enter_door", [this](const QHttpServerRequest &request) {
        QElapsedTimer timer;
        timer.start();

        auto req = request.query().queryItems().at(0);
        if (req.first != "rfid")
            qWarning() << "first param must be rfid!";
        auto rfid = req.second;
        auto time = QDateTime::currentDateTime().toString("hh:mm");
        bool isVlid = this->database->isValid(rfid);
        this->database->addLogInTime(rfid);
        Q_EMIT newUser(this->database->getLastLog());

        req = request.query().queryItems().at(1);
        if (req.first != "delay")
            qWarning() << "second param must be delay!";
        auto delay = req.second;
        qDebug() << "Arduino Delay : " << delay.toStdString() << "ms";
        qDebug() << "server Delay : " << timer.nsecsElapsed() / (float) 1000 << "ms";

        return time + (isVlid ? "ok" : "no");
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

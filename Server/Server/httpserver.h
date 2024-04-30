#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QtHttpServer/QHttpServer>
#include <QtHttpServer/QHttpServerResponse>
#include "database.h"

class HttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer(Database *database, QObject *parent = nullptr);

Q_SIGNALS:
    void newUser(QJsonObject lastLog);

private:
    Database *database;
};

#endif // HTTPSERVER_H

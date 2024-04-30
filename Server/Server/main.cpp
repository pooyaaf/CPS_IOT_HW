// Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>

#include "database.h"
#include "httpserver.h"
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Database database;

    auto websocketServer = new WebsocketServer(&database, 1234, true);
    QObject::connect(websocketServer, &WebsocketServer::closed, &a, &QCoreApplication::quit);

    auto httpServer = new HttpServer(&database);
    QObject::connect(httpServer, &HttpServer::newUser, websocketServer, &WebsocketServer::onNewUser);

    return a.exec();
}

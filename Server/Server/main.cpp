// Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCoreApplication>
#include "database.h"
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Database database;

    Server *server = new Server(&database, 1234, true);
    QObject::connect(server, &Server::closed, &a, &QCoreApplication::quit);

    database.addLogInTime("ali");
    database.addLogInTime("mmd");
    database.addLogInTime("ask");
    database.addLogInTime("fubn");

    qDebug() << database.getLogs();

    return a.exec();
}

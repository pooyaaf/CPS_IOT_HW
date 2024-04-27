#include <QCoreApplication>
#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    WebSocketServer server;

    return app.exec();
}

// Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
#include "client.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

Client::Client(QObject *parent)
    : QObject(parent)
    , m_debug(true)
{}

void Client::connectToServer(const QString &address,
                             const QString &username,
                             const QString &password)
{
    QUrl url;
    url.setPort(1234);
    url.setScheme("ws");
    //url.setHost(address);
    url.setHost("localhost");

    this->username = username;
    this->password = password;

    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);
    m_webSocket.open(url);
}

void Client::closed()
{
    if (m_debug)
        qDebug() << "closed!";
    disconnect(&m_webSocket, &QWebSocket::textMessageReceived, 0, 0);
    disconnect(&m_webSocket, &QWebSocket::connected, 0, 0);
    disconnect(&m_webSocket, &QWebSocket::disconnected, 0, 0);
    Q_EMIT connectionChanged(true);
}

void Client::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    Q_EMIT connectionChanged(false);
    //auto message = "login|"+username + "|" + password;
    auto message = QString("login|admin|admin");
    m_webSocket.sendTextMessage(message);
    if (m_debug)
        qDebug() << "send: " + message;
}

QJsonArray Client::getHistory()
{
    m_webSocket.sendTextMessage("log");
    return cachedData;
}

void Client::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    auto rcvd_msg = message.split("|");
    if (rcvd_msg[0] == "login") {
        if (rcvd_msg[1] == "ok") {
            //TODO
        } else
            m_webSocket.close();
    } else if (rcvd_msg[0] == "log") {
        cachedData = QJsonDocument::fromJson(rcvd_msg[1].toUtf8()).array();
        qDebug() << "rcvd logs";
        Q_EMIT onHistoryUpdated(cachedData);
    }
}

#include "clientconnection.h"
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include "codevalidator.h" // Include CodeValidator header

ClientConnection::ClientConnection(QTcpSocket *socket, QObject *parent):
    QObject(parent),
    m_socket(socket),
    m_validator() // Instantiate CodeValidator
{
    connect(m_socket.get(), &QAbstractSocket::disconnected, this, &QObject::deleteLater);
    connect(m_socket.get(), &QIODevice::readyRead, this, &ClientConnection::readyRead);
}
void ClientConnection::readyRead()
{
    while ((m_state == ConnectionState::RequestLine || m_state == ConnectionState::RequestHeaders)
           && m_socket->canReadLine())
    {
        auto line = m_socket->readLine();
        if (line.endsWith("\r\n"))
            line.chop(2);

        if (m_state == ConnectionState::RequestLine)
        {
            const auto parts = line.split(' ');
            if (parts.size() != 3)
            {
                qWarning() << "Request part doesn't contain three parts:" << line;
                deleteLater();
                return;
            }
            m_request.method = parts.at(0);
            m_request.path = parts.at(1);
            m_request.protocol = parts.at(2);

            m_state = ConnectionState::RequestHeaders;
            continue;
        }
        else
        {
            if (line.isEmpty())
            {
                if (m_request.contentLength)
                {
                    m_state = ConnectionState::RequestBody;
                    continue;
                }
                else
                {
                    m_state = ConnectionState::Response;
                    sendResponse();
                }
            }
            static const QRegularExpression expr("^([^:]+): +(.*)$");
            const auto match = expr.match(line);
            if (!match.hasMatch())
            {
                qWarning() << "could not parse header" << line;
                deleteLater();
                return;
            }
            const auto name = match.captured(1);
            const auto value = match.captured(2);

            m_request.headers[name] = value;

            if (name == "Content-Length")
            {
                bool ok;
                m_request.contentLength = value.toInt(&ok);
                if (!ok)
                {
                    qWarning() << "could not parse Content-Length:" << line;
                    deleteLater();
                    return;
                }
            }
            continue;
        }
    }

    if (m_state == ConnectionState::RequestBody)
    {
        m_request.body.append(m_socket->read(m_request.contentLength - m_request.body.size()));
        Q_ASSERT(m_request.body.size() <= m_request.contentLength);
        if (m_request.body.size() == m_request.contentLength)
        {
            // Trim leading and trailing whitespace characters
            QString receivedId = QString::fromUtf8(m_request.body).trimmed();
            if ( (receivedId.length() - 139) == 10)
            {
                // Validate the ID using CodeValidator
                bool isValidId = m_validator.isValid(receivedId);
                if (isValidId)
                {
                    qDebug() << "Received ID is valid.";
                }
                else
                {
                    qDebug() << receivedId;
                    qDebug() << "Received ID is invalid.";
                }
            }
            else
            {
                qDebug() << receivedId.length() - 139;
                qDebug() << "Received data is not a 10-character ID.";
            }

            // Reset the state for the next request
            m_state = ConnectionState::Response;
            sendResponse();
            return;
        }
    }
}


void ClientConnection::sendResponse()
{
    QString content;
    content += "<h1>Hello World!</h1>";
    content += QString("<p>Method: %0 Path: %1 Protocol: %2</p>")
                   .arg(m_request.method.toHtmlEscaped(),
                        m_request.path.toHtmlEscaped(),
                        m_request.protocol.toHtmlEscaped());
    content += "<h2>Headers:</h2>";
    content += "<table><thead><tr><th>Name</th><th>Value</th></tr></thead><tbody>";
    for(auto iter = m_request.headers.begin(); iter != m_request.headers.end(); iter++)
        content += QString("<tr><td>%0</td><td>%1</td></tr>")
                       .arg(iter.key().toHtmlEscaped(), iter.value().toHtmlEscaped());
    content += "</tbody></table>";
    if(m_request.body.size())
    {
        content += "<h2>Request-Body:</h2>";
        content += "<pre>" + QString::fromUtf8(m_request.body).toHtmlEscaped() + "</pre>";
    }

    content += "<form method=\"POST\" enctype=\"multipart/form-data\">"
               "<input name=\"input_name\" type=\"text\" />"
               "<button type=\"submit\">SEND</button>"
               "</form>";
    const auto encoded = content.toUtf8();

    m_socket->write("HTTP/1.1 200 Ok\r\n");
    m_socket->write("Content-Type text/html\r\n");
    m_socket->write(QString("Content-Length: %0\r\n").arg(encoded.size()).toUtf8());
    m_socket->write("\r\n");
    m_socket->write(encoded);

    m_state = ConnectionState::RequestLine;
    m_request = {};
}

ClientConnection::~ClientConnection() = default;

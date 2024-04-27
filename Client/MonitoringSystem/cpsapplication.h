#ifndef CPSAPPLICATION_H
#define CPSAPPLICATION_H

#include <QApplication>
#include <QJsonArray>
#include <QObject>

#include "client.h"
#include "cpshistorywindow.h"
#include "cpsmainwindow.h"

namespace CPS {

class Application : public QObject
{
    Q_OBJECT

public:

    explicit Application(QObject *parent = nullptr);
    ~Application();

    void show();

Q_SIGNALS:

private Q_SLOTS:
    void showHistoryWindow();
    void updateHistoryWindow(QJsonArray data);

private: // methods

private: // members
    MainWindow    *_window;
    HistoryWindow *_history;
    Client *_client;
};

} // end of CPS

#endif // CPSAPPLICATION_H

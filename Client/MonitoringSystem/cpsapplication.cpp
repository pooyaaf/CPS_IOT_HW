#include "cpsapplication.h"
#include "cpswindowsapitools.h"

namespace CPS {

Application::Application(QObject *parent)
    : QObject{parent}
    , _window(new MainWindow)
    , _history(new HistoryWindow)
    , _client(new Client)
{
    setWindowsThemeToDark<MainWindow>(*_window);

    connect(_window, &MainWindow::historyuBtnClicked, this, &Application::showHistoryWindow);
    connect(_client, &Client::newUser, _window, &MainWindow::showUserDetails);
    connect(_window, &MainWindow::connectBtnClicked, _client, &Client::connectToServer);
    connect(_client, &Client::connectionChanged, _window, &MainWindow::changeRightPanelEnabled);
    connect(_client, &Client::onHistoryUpdated, this, &Application::updateHistoryWindow);
}

Application::~Application()
{
    delete this->_window;
    delete this->_history;
    delete this->_client;
}

void Application::show()
{
    this->_window->show();
}

void Application::updateHistoryWindow(QJsonArray data)
{
    qDebug() << "update";
    _history->show(data);
}

void Application::showHistoryWindow()
{
    setWindowsThemeToDark<HistoryWindow>(*_history);
    _client->getHistory();
}

} // end of CPS

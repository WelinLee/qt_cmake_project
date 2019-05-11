#include "QSingleApplication.h"
#include <QLocalSocket>
#include <QFileInfo>
#include <QWidget>
#include <QDebug>

#define TIME_OUT                (500)

QSingleApplication::QSingleApplication(int &argc, char **argv):QApplication(argc, argv)
  , _isRunning(false)
  , _localServer(nullptr)
{
    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    _initLocalConnection();
}

void QSingleApplication::SetBaseWindow(IBaseWindow *w)
{
    m_w = w;
}

bool QSingleApplication::isRunning()
{
    return _isRunning;
}

void QSingleApplication::_newLocalConnection()
{
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket)
    {
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;

        _activateWindow();
    }
}

void QSingleApplication::_initLocalConnection()
{
    _isRunning = false;

    QLocalSocket socket;
    socket.connectToServer(_serverName);
    if(socket.waitForConnected(TIME_OUT))
    {
        qDebug() << QString("%1 already running.").arg(_serverName);
        _isRunning = true;
        return;
    }

    _newLocalServer();
}

void QSingleApplication::_newLocalServer()
{
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName))
    {
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError)
        {
            QLocalServer::removeServer(_serverName);
            _localServer->listen(_serverName);
        }
    }
}

void QSingleApplication::_activateWindow()
{
    if(m_w)
    {
        m_w->RaiseShow();
    }
}

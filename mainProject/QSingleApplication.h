#pragma once

#include <QApplication>
#include <QLocalServer>
#include "SrcUI/MainWindow.h"

class QSingleApplication : public QApplication
{
    Q_OBJECT

public:
    QSingleApplication(int &argc, char **argv);
    void SetBaseWindow(IBaseWindow *w);
    bool isRunning();
    IBaseWindow *m_w = nullptr;

private slots:
    void _newLocalConnection();	       // new connect trigger

private:
    void _initLocalConnection();	      //init local connect
    void _newLocalServer();		      // create server
    void _activateWindow();		      // active window

    bool _isRunning;                           // to detect APP is running
    QLocalServer *_localServer;       // local socket Server
    QString _serverName;                 // service name
};



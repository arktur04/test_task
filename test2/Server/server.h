// server.h

#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "client.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:

public slots:

};


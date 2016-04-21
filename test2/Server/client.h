// client.h

#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void setSocket(qintptr Descriptor);

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
private:
    QTcpSocket *socket;
};


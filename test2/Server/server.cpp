// server.cpp

#include "server.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent) {
}

void MyServer::startServer()
{
    if(listen(QHostAddress::Any, 1234)){
        qDebug() << "Сервер запущен";
    } else {
        qDebug() << "Сервер не запущен";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor) {
    // При входящем соединении создаем объект клиента
    // и устанавливаем сокет
    Client *client = new Client(this);
    client->setSocket(socketDescriptor);
}

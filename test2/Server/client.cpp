// client.cpp
#include <QScriptEngine>
#include <QDateTime>
#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent) {
}

void Client::setSocket(qintptr descriptor) {
    // создание нового сокета
    socket = new QTcpSocket(this);
    qDebug() << "Установлено новое соединение";
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->setSocketDescriptor(descriptor);
    qDebug() << "Cокет " << descriptor;
}


// asynchronous
void Client::connected() {
    qDebug() << "Клиент подключен";
}

// asynchronous
void Client::disconnected() {
    qDebug() << "Клиент отключен";
}

void Client::readyRead() {
    //получаем сообщение от клиента
    qDebug() << "Сообщение от клиента:";
    QString str = socket->readAll();
    qDebug() << str;
    //вычисляем значение
    QScriptEngine engine;
    QScriptValue val = engine.evaluate(str);
    //текущая дата
    QDateTime time = QDateTime::currentDateTime();
    //отправляем тезультат клиенту
    QString res = val.toString();
    qDebug() << "результат: " << res;
    qDebug() << "время: " << time.toString(Qt::ISODate);
    socket->write(res.toLatin1());
}

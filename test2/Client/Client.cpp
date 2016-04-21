// ======================================================================
//  Client.cpp
// ======================================================================

#include <QtWidgets>
#include <QtGui>
#include "Client.h"
#include <QSettings>

// ----------------------------------------------------------------------
Client::Client(QWidget* pwgt): QWidget(pwgt) {
    // создаем объект настроек программы
    settings = new QSettings("Test", "Calculator");
    // создаем объект сокета
    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(slotError(QAbstractSocket::SocketError)));
    //----------------------------
    //GUI
    //----------------------------
    QGridLayout* gLayout = new QGridLayout;
    // поле адреса сервера
    m_servInput = new QLineEdit;
    gLayout->addWidget(m_servInput, 0, 0, 1, 2);
    // поле номера порта
    m_portInput = new QLineEdit;
    gLayout->addWidget(m_portInput, 0, 2, 1, 1);
    // кнопка подключения к серверу
    QPushButton* pConnect = new QPushButton("Подкл");
    // окно сообщений от сервера
    m_ptxtInfo  = new QTextEdit;
    gLayout->addWidget(pConnect, 0, 3, 1, 1);
    connect(pConnect, SIGNAL(clicked()), SLOT(slotConnect()));
    m_ptxtInfo->setReadOnly(true);
    gLayout->addWidget(m_ptxtInfo, 1, 0, 1, 4);
    // строка ввода выражения
    m_ptxtInput = new QLineEdit;
    connect(m_ptxtInput, SIGNAL(returnPressed()), 
            this, SLOT(slotSendToServer()));
    m_ptxtInput->setReadOnly(true);
    gLayout->addWidget(m_ptxtInput, 2, 0, 1, 4);
    //кнопки 0-9, +, -, *, /
    QPushButton* btn[14];
    //создаем и размещаем кнопки 0-9, -, +, *, /
    for(int i = 0; i < 14; ++i) {
        btn[i] = new QPushButton(str[i]);
        gLayout->addWidget(btn[i], i / 4 + 3, i % 4, 1, 1);
        connect(btn[i], SIGNAL(clicked()),
                    this, SLOT(slotOnBtnClick()));
    }
    //кнопка =
    QPushButton* pSend = new QPushButton("=");
    connect(pSend, SIGNAL(clicked()), SLOT(slotSendToServer()));
    gLayout->addWidget(pSend, 6, 2, 1, 2);
    //-----
    setLayout(gLayout);
    // устанавливаем соединение
    connectToHost();
}

// ----------------------------------------------------------------------
void Client::connectToHost() {
    // читаем адрес сервера и номер порта из конфигурации
    // и устанавливаем соединение с сервером
    QString host = settings->value("hostname", "localhost").toString();
    m_servInput->setText(host);
    quint16 port = settings->value("port", 1234).toInt();
    m_portInput->setText(QString::number(port));
    m_pTcpSocket->connectToHost(host, port);
}

void Client::slotOnBtnClick() {
   //при нажатии на кнопку 0-9, +, -, *, /
   // добавляем соответствующий символ к строке ввода
   QPushButton* btn = static_cast<QPushButton*>( sender());
   m_ptxtInput->setText(m_ptxtInput->text() + btn->text());
}


// ----------------------------------------------------------------------
void Client::slotReadyRead() {
    //читаем сообщения от сервера
    QString str = m_pTcpSocket->readAll();
    //помещаем сообщения от сервера в окно
    m_ptxtInfo->append("сообщение от сервера:");
    m_ptxtInfo->append(str);
    //помещаем время получения сообщения
    QDateTime time = QDateTime::currentDateTime();
    m_ptxtInfo->append("время получения:");
    m_ptxtInfo->append(time.toString(Qt::ISODate));
}

// ----------------------------------------------------------------------
void Client::slotError(QAbstractSocket::SocketError err) {
    //сообщения об ошибках сервера
    QString strError = "Ошибка: " + (err == QAbstractSocket::HostNotFoundError ?
                     "Хост не найден" :
                     err == QAbstractSocket::RemoteHostClosedError ? 
                     "Соединение закрыто" :
                     err == QAbstractSocket::ConnectionRefusedError ? 
                     "Соединение не установлено" :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtInfo->append(strError);
}

// ----------------------------------------------------------------------
void Client::slotSendToServer() {
    //отправляем выражение на сервер
    QString toSend = m_ptxtInput->text();
    m_pTcpSocket->write(toSend.toStdString().data());
    // и очищаем строку ввода
    m_ptxtInput->setText("");
    //помещаем строку в окно сообщений
    m_ptxtInfo->append("отправка на сервер:");
    m_ptxtInfo->append(toSend);
    //помещаем время отправки в окно сообщений
    QDateTime time = QDateTime::currentDateTime();
    m_ptxtInfo->append("время отправки:");
    m_ptxtInfo->append(time.toString(Qt::ISODate));
}

// ------------------------------------------------------------------
void Client::slotConnected() {
    m_ptxtInfo->append("Соединение с сервером установлено");
}

void Client::slotConnect() {
    //читаем параметры конфигурации
    settings->setValue("hostname", m_servInput->text());
    settings->setValue("port", m_portInput->text().toUInt());
    //отключаемся от сервера
    m_pTcpSocket->disconnectFromHost();
    //и подключаемся к серверу снова
    connectToHost();
}

// ======================================================================
//  Client.h
// ======================================================================

#pragma once

#include <QWidget>
#include <QTcpSocket>
#include <QSettings>

class QTextEdit;
class QLineEdit;

// ======================================================================
class Client : public QWidget {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket; // объект сокета
    QTextEdit* m_ptxtInfo; // окно сообщений от сервера
    QLineEdit* m_ptxtInput; // строка ссодимого выражения
    QLineEdit* m_servInput; //строка адреса сервера
    QLineEdit* m_portInput; //строка порта сервера
    QString str[15] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "-", "*", "/", "="};
    QSettings* settings; //сохранение настроек
public:
    Client(QWidget* pwgt = 0) ;
    void connectToHost(); //устанавливает соединение по текущему адресу и порту
    ~Client() {delete settings;}
private slots:
    void slotReadyRead(); //получение сообщения от сервера
    void slotError(QAbstractSocket::SocketError); //ошибка сокета
    void slotSendToServer(); //нажатие на кнопку =
    void slotOnBtnClick(); //нажатия на кнопки 0-9, +, -, *, /
    void slotConnected(); //соединение установлено
    void slotConnect(); //нажатие на кнопку "Подкл"
};

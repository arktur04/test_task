#-------------------------------------------------
#
# Project created by QtCreator 2013-09-19T18:58:06
#
#-------------------------------------------------

QT       += core network script
QT       -= gui

TARGET = AsyncQTcpServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client.cpp \
    server.cpp

HEADERS += \
    client.h \
    server.h

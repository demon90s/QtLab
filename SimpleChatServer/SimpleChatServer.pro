#-------------------------------------------------
#
# Project created by QtCreator 2019-12-17T21:26:31
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleChatServer
TEMPLATE = app


SOURCES += main.cpp\
        simplechatserver.cpp

HEADERS  += simplechatserver.h

FORMS    += simplechatserver.ui

CONFIG   += c++11

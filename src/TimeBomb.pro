#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T08:08:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeBomb
TEMPLATE = app
PKGCONFIG += openssl

SOURCES += main.cpp\
        mainwindow.cpp \
    mythread.cpp \
    simplecrypt.cpp \
    avgthread.cpp \
    big_number.cpp

HEADERS  += mainwindow.h \
    mythread.h \
    simplecrypt.h \
    avgthread.h

FORMS    += mainwindow.ui

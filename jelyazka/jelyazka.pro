#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T23:10:28
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jelyazka
TEMPLATE = app
INCLUDEPATH += ../resources/boost_1_70_0/ #The path to the Boost libraries.


SOURCES += main.cpp\
    search.cpp \
    logger.cpp \
    initwindow.cpp \
    Options/optionswindow.cpp \
    refreshfeedsdata.cpp \
    help.cpp \
    about.cpp \
    rssdata.cpp \
    rssarticle.cpp \
    http.cpp \
    parserss.cpp \
    data.cpp \
    rssthread.cpp \
    notificationwindow.cpp \
    database.cpp \
    rsssearchgui.cpp \
    rsssearchguithread.cpp \
    trayicon.cpp \
    initialization.cpp \
    mainwindow.cpp

HEADERS  += \
    search.h \
    logger.h \
    initwindow.h \
    Options/optionswindow.h \
    refreshfeedsdata.h \
    help.h \
    about.h \
    rssdata.h \
    rssarticle.h \
    http.h \
    parserss.h \
    data.h \
    rssthread.h \
    notificationwindow.h \
    database.h \
    rsssearchgui.h \
    rsssearchthread.h \
    trayicon.h \
    initialization.h \
    mainwindow.h

FORMS    += \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui \
    notificationwindow.ui \
    rsssearchgui.ui \
    initialization.ui \
    mainwindow.ui

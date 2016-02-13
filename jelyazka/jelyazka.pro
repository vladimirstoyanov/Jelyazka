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
INCLUDEPATH += D:/boost_1_60_0/ #The path to the Boost libraries.


SOURCES += main.cpp\
        mainwindow.cpp \
    viewwindow.cpp \
    search.cpp \
    animatewindow.cpp \
    logger.cpp \
    initwindow.cpp \
    Options/optionswindow.cpp \
    refreshfeedsdata.cpp \
    help.cpp \
    about.cpp \
    db.cpp \
    rssdata.cpp \
    rssarticle.cpp \
    http.cpp \
    parserss.cpp \
    data.cpp \
    web_search.cpp \
    web_search_thread.cpp \
    rssthread.cpp

HEADERS  += mainwindow.h \
    viewwindow.h \
    search.h \
    animatewindow.h \
    logger.h \
    initwindow.h \
    Options/optionswindow.h \
    refreshfeedsdata.h \
    help.h \
    about.h \
    db.h \
    rssdata.h \
    rssarticle.h \
    http.h \
    parserss.h \
    data.h \
    web_search.h \
    web_search_thread.h \
    rssthread.h

FORMS    += mainwindow.ui \
    viewwindow.ui \
    animatewindow.ui \
    web_search_interface.ui \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui

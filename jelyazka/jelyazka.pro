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
INCLUDEPATH += D:/boost_1_55_0/ #The path to the Boost libraries.


SOURCES += main.cpp\
        mainwindow.cpp \
    sitestruct.cpp \
    viewwindow.cpp \
    search.cpp \
    animatewindow.cpp \
    logger.cpp \
    web_search_interface.cpp \
    web_search_interface_thread.cpp \
    initwindow.cpp \
    optionswindow.cpp \
    refreshfeedsdata.cpp \
    help.cpp \
    about.cpp \
    db.cpp \
    rssdata.cpp \
    rssarticle.cpp \
    http.cpp

HEADERS  += mainwindow.h \
    sitestruct.h \
    viewwindow.h \
    search.h \
    animatewindow.h \
    logger.h \
    web_search_interface.h \
    web_search_interface_thread.h \
    initwindow.h \
    optionswindow.h \
    refreshfeedsdata.h \
    help.h \
    about.h \
    db.h \
    rssdata.h \
    rssarticle.h \
    http.h

FORMS    += mainwindow.ui \
    viewwindow.ui \
    animatewindow.ui \
    web_search_interface.ui \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui

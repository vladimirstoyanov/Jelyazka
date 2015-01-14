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
INCLUDEPATH += /mnt/sda2/Programing/boost_1_57_0/ #The path to the Boost libraries.
RC_FILE = icon.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    net.cpp \
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
    about.cpp

HEADERS  += mainwindow.h \
    net.h \
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
    about.h

FORMS    += mainwindow.ui \
    viewwindow.ui \
    animatewindow.ui \
    web_search_interface.ui \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui

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
CONFIG += c++11

SOURCES += main.cpp\
    search.cpp \
    logger.cpp \
    InitWindow/initwindow.cpp \
    InitWindow/init_window_thread.cpp \
    Options/optionswindow.cpp \
    refreshfeedsdata.cpp \
    help.cpp \
    about.cpp \
    RSS/rssdata.cpp \
    RSS/rssarticle.cpp \
    http.cpp \
    RSS/parserss.cpp \
    data.cpp \
    rssthread.cpp \
    notificationwindow.cpp \
    database.cpp \
    rsssearchgui.cpp \
    rsssearchguithread.cpp \
    trayicon.cpp \
    initialization.cpp \
    mainwindow.cpp \
    JelayzkaStateMachine/state.cpp \
    JelayzkaStateMachine/idle_state.cpp \
    JelayzkaStateMachine/init_window_state.cpp \
    JelayzkaStateMachine/main_window_state.cpp \
    JelayzkaStateMachine/option_window_state.cpp \
    JelayzkaStateMachine/remove_old_data_state.cpp \
    JelayzkaStateMachine/rss_data_updated_state.cpp \
    JelayzkaStateMachine/update_settings_state.cpp \
    JelayzkaStateMachine/jelyazka_state_machine.cpp \
    JelayzkaStateMachine/transition.cpp \
    JelayzkaStateMachine/help_window_state.cpp \
    JelayzkaStateMachine/rss_search_window_state.cpp \
    jelyazkamanager.cpp

HEADERS  += \
    search.h \
    logger.h \
    InitWindow/initwindow.h \
    InitWindow/init_window_thread.h \
    Options/optionswindow.h \
    refreshfeedsdata.h \
    help.h \
    about.h \
    RSS/rssdata.h \
    RSS/rssarticle.h \
    http.h \
    RSS/parserss.h \
    data.h \
    rssthread.h \
    notificationwindow.h \
    database.h \
    rsssearchgui.h \
    rsssearchthread.h \
    trayicon.h \
    initialization.h \
    mainwindow.h \
    JelayzkaStateMachine/state.hpp \
    JelayzkaStateMachine/idle_state.hpp \
    JelayzkaStateMachine/init_window_state.hpp \
    JelayzkaStateMachine/main_window_state.hpp \
    JelayzkaStateMachine/option_window_state.hpp \
    JelayzkaStateMachine/remove_old_data_state.hpp \
    JelayzkaStateMachine/rss_data_updated_state.hpp \
    JelayzkaStateMachine/update_settings_state.hpp \
    JelayzkaStateMachine/jelyazka_state_machine.hpp \
    JelayzkaStateMachine/transition.hpp \
    JelayzkaStateMachine/help_window_state.hpp \
    JelayzkaStateMachine/rss_search_window_state.hpp \
    jelyazkamanager.h

FORMS    += \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui \
    notificationwindow.ui \
    rsssearchgui.ui \
    mainwindow.ui

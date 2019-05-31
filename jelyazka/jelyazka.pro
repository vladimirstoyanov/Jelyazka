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
    JelayzkaStateMachine/add_rss_data_state.cpp \
    search.cpp \
    logger.cpp \
    InitWindow/initwindow.cpp \
    Options/optionswindow.cpp \
    help.cpp \
    about.cpp \
    RSS/rssdata.cpp \
    RSS/rssarticle.cpp \
    http.cpp \
    RSS/parserss.cpp \
    data.cpp \
    notificationwindow.cpp \
    database.cpp \
    rsssearchgui.cpp \
    rsssearchguithread.cpp \
    trayicon.cpp \
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
    JelayzkaStateMachine/tray_icon_state.cpp \
    JelayzkaStateMachine/about_window_state.cpp \
    jelyazkamanager.cpp \
    RSS/refresh_rss_data.cpp \
    Options/settings.cpp \
    RSS/update_rss_data.cpp \
    InitWindow/download_rss_data_thread.cpp

HEADERS  += \
    JelayzkaStateMachine/add_rss_data_state.hpp \
    search.h \
    logger.h \
    InitWindow/initwindow.h \
    Options/optionswindow.h \
    help.h \
    about.h \
    RSS/rssdata.h \
    RSS/rssarticle.h \
    http.h \
    RSS/parserss.h \
    data.h \
    notificationwindow.h \
    database.h \
    rsssearchgui.h \
    rsssearchthread.h \
    trayicon.h \
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
    JelayzkaStateMachine/tray_icon_state.hpp \
    JelayzkaStateMachine/about_window_state.hpp \
    jelyazkamanager.h \
    RSS/refresh_rss_data.h \
    Options/settings.h \
    RSS/update_rss_data.h \
    InitWindow/download_rss_data_thread.h

FORMS    += \
    initwindow.ui \
    optionswindow.ui \
    help.ui \
    about.ui \
    notificationwindow.ui \
    rsssearchgui.ui \
    mainwindow.ui

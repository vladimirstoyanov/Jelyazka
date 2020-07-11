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
    http.cpp \
    data.cpp \
    database.cpp \
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
    RSS/refresh_rss_data.cpp \
    settings.cpp \
    RSS/update_rss_data.cpp \
    RSS/download_rss_data_thread.cpp \
    GUI/about_window.cpp \
    GUI/help_window.cpp \
    GUI/main_window.cpp \
    GUI/init_window.cpp \
    GUI/notification_window.cpp \
    GUI/options_window.cpp \
    GUI/rss_search_window.cpp \
    GUI/tray_icon.cpp \
    RSS/rss_search_thread.cpp \
    RSS/rss_article.cpp \
    RSS/rss_data.cpp \
    RSS/parse_rss.cpp \
    jelyazka_manager.cpp

HEADERS  += \
    JelayzkaStateMachine/add_rss_data_state.hpp \
    search.h \
    logger.h \
    http.h \
    data.h \
    database.h \
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
    RSS/refresh_rss_data.h \
    settings.h \
    RSS/update_rss_data.h \
    RSS/download_rss_data_thread.h \
    GUI/about_window.h \
    GUI/help_window.h \
    GUI/init_window.h \
    GUI/main_window.h \
    GUI/notification_window.h \
    GUI/options_window.h \
    GUI/rss_search_window.h \
    GUI/tray_icon.h \
    RSS/rss_search_thread.h \
    RSS/rss_article.h \
    RSS/rss_data.h \
    RSS/parse_rss.h \
    jelyazka_manager.h

FORMS    += \
    GUI/initwindow.ui \
    GUI/optionswindow.ui \
    GUI/help.ui \
    GUI/about.ui \
    GUI/notificationwindow.ui \
    GUI/rsssearchgui.ui \
    GUI/mainwindow.ui

/*
    mainwindow.h
    Jelyazka RSS/RDF reader
    Copyright (C) 2014 Vladimir Stoyanov
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

#include "rssthread.h"
#include "viewwindow.h"
#include "notificationwindow.h"
#include "initwindow.h"
#include "refreshfeedsdata.h"
//#include "about.h"
#include "data.h"
#include "trayicon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /*explicit*/ MainWindow(InitWindow *window);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui_;
    //QSystemTrayIcon *tray_icon_;
    //QMenu *tray_icon_menu_;
    //QAction *about_;
    //QAction *close_;
    //QAction *view_;
    TrayIcon * tray_icon_;
    ViewWindow *view_window_;
    NotificationWindow *notification_window_;
    RSSThread *rss_thread_;
    Data *data_;
    RefreshFeedsData *refresh_feed_data_;
    //About *about_gui_;

    //void createActions();
    //void createTrayIcon();
    //void setIcon();
    //void closeEvent(QCloseEvent *); // Overriding the window's close event

public slots:
    void onDone();
private slots:
    //void trayIconClicked(QSystemTrayIcon::ActivationReason);
    //void viewWindow();
    //void showAbout();
};

#endif // MAINWINDOW_H

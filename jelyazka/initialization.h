/*
    initialization.h
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
#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <QCloseEvent>
#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>

#include "data.h"
#include "initwindow.h"
#include "mainwindow.h"
#include "notificationwindow.h"
#include "refreshfeedsdata.h"
#include "rssthread.h"
#include "trayicon.h"

namespace Ui {
class Initialization;
}

class Initialization : public QMainWindow
{
    Q_OBJECT
    
public:
    /*explicit*/ Initialization(InitWindow *window);
    virtual ~Initialization();

public slots:
    void onDone();

private:
    Ui::Initialization *ui_;
    TrayIcon * tray_icon_;
    MainWindow *main_window_;
    NotificationWindow *notification_window_;
    RSSThread *rss_thread_;
    Data *data_;
    RefreshFeedsData *refresh_feed_data_;

};

#endif // INITIALIZATION_H

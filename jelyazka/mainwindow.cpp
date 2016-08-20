/*
    mainwindow.cpp
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
#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"
#include <vector>

MainWindow::MainWindow(InitWindow *init_window)
{
    //init class pointers
    tray_icon_=NULL;
    tray_icon_menu_=NULL;
    about_ = NULL;
    close_ = NULL;
    view_ = NULL;
    rss_thread_=NULL;
    view_window_=NULL;
    notification_window_=NULL;

    //creating system tray icon
    createActions();
    createTrayIcon();
    setIcon();

    //init animate window
    notification_window_ = new NotificationWindow();

    //when init window done its work emit Done funtion
    connect(init_window,SIGNAL(Done()),this,SLOT(onDone()));

    //initialize site_struct class
    data_ = new Data();
    rss_thread_ = new RSSThread(data_);
    rss_thread_->setAutoDelete(false);


    //initialize viewwindow class
    view_window_ = new ViewWindow(0, rss_thread_,data_);
    refresh_feed_data_ = new RefreshFeedsData(0, rss_thread_, data_);

    //load data
    init_window->setSignal(rss_thread_, data_);

    //set thread signal
    notification_window_->setSignal(rss_thread_, data_);

    //init About window
    about_gui_ = new About();

    this->hide();
}

MainWindow::~MainWindow()
{
    if (tray_icon_!=NULL)
        delete tray_icon_;
    if (tray_icon_menu_!=NULL)
        delete tray_icon_menu_;
    if (about_!=NULL)
        delete about_;
    if (close_!=NULL)
        delete close_;
    if (view_!=NULL)
        delete view_;
    rss_thread_->deleteLater();
    if (view_window_!=NULL)
        delete view_window_;
    if (notification_window_!=NULL)
        delete notification_window_;
    if (data_!=NULL)
        delete data_;

    delete about_gui_;
}
void MainWindow::viewWindow()
{
    view_window_->show();
}

void MainWindow::showAbout()
{
    about_gui_->show();
}

void MainWindow::createActions()
{
    view_ = new QAction(tr("&Open Jelyazka"), this);
    connect(view_, SIGNAL(triggered()), this, SLOT(viewWindow()));

    about_ = new QAction(tr("&About"), this);
    connect(about_, SIGNAL(triggered()), this, SLOT(showAbout()));

    close_ = new QAction(tr("&Quit"), this);
    connect(close_, SIGNAL(triggered()), qApp, SLOT(quit()));
}
void MainWindow::createTrayIcon()
{
    tray_icon_menu_ = new QMenu(this);

    tray_icon_menu_->addAction(view_);
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(about_);
    tray_icon_menu_->addSeparator();
    tray_icon_menu_->addAction(close_);


    tray_icon_ = new QSystemTrayIcon(this);
    tray_icon_->setContextMenu(tray_icon_menu_);


    connect(
            tray_icon_,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
}

void MainWindow::setIcon()
{
    tray_icon_->setIcon(QIcon("../resources/Jelyazka_icon.png"));
}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        view_window_->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (tray_icon_->isVisible()) {
        tray_icon_->showMessage(tr("Still here!!!"),
        tr("This application is still running. To quit please click this icon and select Quit"));
        hide();


        event->ignore(); // Don't let the event propagate to the base class
    }
}

void MainWindow::onDone()
{
    tray_icon_->show();
    view_window_->show();
    refresh_feed_data_->start();
    for (uint i=0; i<data_->size(); i++)
      rss_thread_->data_for_animatewindow_+="<index=" + QString::number(i) + ">";
    rss_thread_->emitAnimateWindow();
}

#endif

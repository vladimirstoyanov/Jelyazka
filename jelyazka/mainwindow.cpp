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
    trayIcon=NULL;
    trayIconMenu=NULL;
    about = NULL;
    close = NULL;
    view = NULL;
    s_struct=NULL;
    view_window=NULL;
    aw=NULL;

    //creating system tray icon
    createActions();
    createTrayIcon();
    setIcon();

    //init animate window
    aw = new CAnimateWindow();

    //when init window done its work emit Done funtion
    connect(init_window,SIGNAL(Done()),this,SLOT(onDone()));

    //initialize site_struct class
    s_struct = new SiteStruct();
    s_struct->setAutoDelete(false);

    //initialize viewwindow class
    view_window = new ViewWindow(0,s_struct);
    rfd = new RefreshFeedsData(0,s_struct);

    //load data
    init_window->setSignal(s_struct);

    //set thread signal
    aw->setSignal(s_struct);

    //init About window
    about_gui = new About();

    this->hide();
}

MainWindow::~MainWindow()
{
    if (trayIcon!=NULL)
        delete trayIcon;
    if (trayIconMenu!=NULL)
        delete trayIconMenu;
    if (about!=NULL)
        delete about;
    if (close!=NULL)
        delete close;
    if (view!=NULL)
        delete view;
    s_struct->deleteLater();
    if (view_window!=NULL)
        delete view_window;
    if (aw!=NULL)
        delete aw;

    delete about_gui;
}
void MainWindow::viewWindow()
{
    view_window->show();
}

void MainWindow::showAbout()
{
    about_gui->show();
}

void MainWindow::createActions()
{
    view = new QAction(tr("&Open Jelyazka"), this);
    connect(view, SIGNAL(triggered()), this, SLOT(viewWindow()));

    about = new QAction(tr("&About"), this);
    connect(about, SIGNAL(triggered()), this, SLOT(showAbout()));

    close = new QAction(tr("&Quit"), this);
    connect(close, SIGNAL(triggered()), qApp, SLOT(quit()));
}
void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);

    trayIconMenu->addAction(view);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(about);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(close);


    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);


    connect(
            trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
}

void MainWindow::setIcon()
{
    trayIcon->setIcon(QIcon("../resources/Jelyazka_icon.png"));
}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
        view_window->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        trayIcon->showMessage(tr("Still here!!!"),
        tr("This application is still running. To quit please click this icon and select Quit"));
        hide();


        event->ignore(); // Don't let the event propagate to the base class
    }
}

void MainWindow::onDone()
{
    trayIcon->show();
    view_window->show();
    rfd->start();
    for (uint i=0; i<s_struct->s_struct.size(); i++)
      s_struct->data_for_animatewindow+="<index=" + QString::number(i) + ">";
    s_struct->emitAnimateWindow();
}

#endif

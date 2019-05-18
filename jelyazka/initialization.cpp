/*
    initialization.cpp
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


#include "initialization.h"

Initialization::Initialization(std::shared_ptr<InitWindow> init_window):
    notification_window_ (std::make_shared<NotificationWindow>()),
    data_ (std::make_shared<Data>())
{
    rss_thread_  = std::make_shared<RSSThread>(data_);
    rss_thread_->setAutoDelete(false);

    main_window_ = std::make_shared<MainWindow>(nullptr, rss_thread_, data_);
    tray_icon_ = std::make_shared<TrayIcon>(nullptr, main_window_);
    refresh_feed_data_ = std::make_shared<RefreshFeedsData>(nullptr, rss_thread_, data_);

    //when init_window is finished, then call onDone funtion
    connect(init_window.get(),SIGNAL(Done()),this,SLOT(onDone()));

    //load data
    //init_window->setSignal(rss_thread_, data_);

    //set thread signal
    notification_window_->setSignal(rss_thread_, data_);

    this->hide();
}

Initialization::~Initialization()
{
    rss_thread_->deleteLater();
}

void Initialization::onDone()
{
    tray_icon_->addIcon();

    main_window_->show();
    refresh_feed_data_->start();
    for (uint i=0; i<data_->size(); i++)
      rss_thread_->data_for_animatewindow_+="<index=" + QString::number(i) + ">";
    rss_thread_->emitAnimateWindow();
}

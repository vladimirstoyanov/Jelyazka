/*
    RefreshRssDataTimer.cpp
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
#include "refresh_rss_data.h"

RefreshRssDataTimer::RefreshRssDataTimer():
    data_base_()
    , init_window_thread_(new InitWindowThread ())
    , thread_pool_(std::make_shared <QThreadPool>(this))
    , time_msec_(60000) //1 minute
    , timer_ (std::make_shared<QTimer> ())
{
    makeConnections ();
}

RefreshRssDataTimer::~RefreshRssDataTimer()
{
    stop();
    thread_pool_->waitForDone();
    //init_window_thread_->deleteLater();
}

void RefreshRssDataTimer::start()
{
    qDebug()<<__PRETTY_FUNCTION__;
    loadRssFeeds();
    timer_->start(time_msec_);
}

void RefreshRssDataTimer::stop()
{
    qDebug()<<__PRETTY_FUNCTION__;
    timer_->stop();
}

void RefreshRssDataTimer::onTimeout()
{
    qDebug()<<__PRETTY_FUNCTION__;
    if (new_articles_.size()>0)
    {
        emit (rssDataUpdated(new_articles_));
    }
    new_articles_.clear(); //ToDo: check for memory leaks
    loadRssFeeds();
    start(); //start the timer
}

void RefreshRssDataTimer::onTimeValueChanged(const int time_msec)
{
    this->time_msec_ = time_msec;
}

void RefreshRssDataTimer::onFavoriteFeedsChanged ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssDataTimer::onWriteData (const RSSData rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;

    data_base_.updateArticles(rss_data);
    new_articles_.push_back(rss_data);
}

void RefreshRssDataTimer::onDownloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssDataTimer::makeConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect(init_window_thread_
            , SIGNAL(writeData(RSSData))
            , this
            , SLOT(onWriteData(RSSData))
            , Qt::QueuedConnection);

    connect(init_window_thread_
            , SIGNAL(downloadFinished())
            , this
            , SLOT(onDownloadFinished())
            , Qt::QueuedConnection);
}

//FIXME: this code is the same like a code in initwindow.cpp.
void RefreshRssDataTimer::loadRssUrls()
{
    qDebug()<<__PRETTY_FUNCTION__<<": loading RSS URLs from DB...";

    std::vector<QString> urls;
    data_base_.getURLs(&urls);

    feeds_.clear(); //ToDo: check for memory leaks

    for (unsigned int i=0; i<urls.size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<urls[i];
        Feed feed;
        feed.setFeedUrl(urls[i]);
        feeds_.push_back(feed);
    }
}

//FIXME: this code is the same like a code in initwindow.cpp.
void RefreshRssDataTimer::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    loadRssUrls();
    init_window_thread_->setURLs(feeds_);


    for (unsigned int i=0; i<feeds_.size(); ++i)
    {
        thread_pool_->start(init_window_thread_);
        qDebug()<<__PRETTY_FUNCTION__<<": after";
    }

    if (feeds_.size() == 0)
    {
        onDownloadFinished();
    }
}

void RefreshRssDataTimer::onStartRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    start();
}

void RefreshRssDataTimer::onStopRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    stop();
}

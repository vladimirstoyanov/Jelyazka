/*
    RefreshRssData.cpp
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

RefreshRssData::RefreshRssData():
    data_base_()
    , download_rss_data_thread_(nullptr)
    , thread_pool_(std::make_shared <QThreadPool>(this))
    , time_msec_(60000) //1 minute
    , timer_ (std::make_shared<QTimer> ())
{
    makeConnections ();
}

RefreshRssData::~RefreshRssData()
{
    stop();
    thread_pool_->waitForDone();
    //download_rss_data_thread_->deleteLater();
}

void RefreshRssData::start()
{
    qDebug()<<__PRETTY_FUNCTION__<<": refresh feeds time: "<<Jelyazka::Settings::getRefreshFeedsTime();
    loadRssFeeds();
    timer_->start(Jelyazka::Settings::getRefreshFeedsTime()*60000);
}

void RefreshRssData::stop()
{
    qDebug()<<__PRETTY_FUNCTION__;
    timer_->stop();
}

void RefreshRssData::onTimeout()
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

void RefreshRssData::onTimeValueChanged(const int time_msec)
{
    this->time_msec_ = time_msec;
}

void RefreshRssData::onFavoriteFeedsChanged ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssData::onWriteData (const RSSData rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;

    data_base_.updateArticles(rss_data);
    new_articles_.push_back(rss_data);
}

void RefreshRssData::onDownloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssData::makeConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect(download_rss_data_thread_
            , SIGNAL(writeData(RSSData))
            , this
            , SLOT(onWriteData(RSSData))
            , Qt::QueuedConnection);

    connect(download_rss_data_thread_
            , SIGNAL(downloadFinished())
            , this
            , SLOT(onDownloadFinished())
            , Qt::QueuedConnection);
}

void RefreshRssData::loadRssUrls()
{
    qDebug()<<__PRETTY_FUNCTION__<<": loading RSS URLs from DB...";

    std::vector<QString> urls;
    urls = data_base_.getURLs();
    feeds_.clear();

    for (unsigned int i=0; i<urls.size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<urls[i];
        Feed feed;
        feed.setFeedUrl(urls[i]);
        feeds_.push_back(feed);
    }
}

void RefreshRssData::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    loadRssUrls();
    if (feeds_.size()>0)
    {
        //FIXME: (when thread_pool finished with init_main_window, it removes the pointer)
        download_rss_data_thread_ = new DownloadRssDataThread ();
        makeConnections ();
        download_rss_data_thread_->setURLs(feeds_);

        for (unsigned int i=0; i<feeds_.size(); ++i)
        {
            thread_pool_->start(download_rss_data_thread_);
            qDebug()<<__PRETTY_FUNCTION__<<": after";
        }
    }

    if (feeds_.size() == 0)
    {
        onDownloadFinished();
    }
}

void RefreshRssData::onStartRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    start();
}

void RefreshRssData::onStopRssRefreshData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    stop();
}

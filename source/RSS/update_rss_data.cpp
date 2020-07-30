/*
    UpdateRssData.cpp
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
#include "update_rss_data.h"

UpdateRssData::UpdateRssData():
    data_base_()
    , download_rss_data_thread_(nullptr)
    , thread_pool_(std::make_shared <QThreadPool>(this))
{
    makeConnections ();
}

UpdateRssData::~UpdateRssData()
{
    thread_pool_->waitForDone();
    //download_rss_data_thread_->deleteLater();
}

void UpdateRssData::onWriteData (RSSData rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;
    //data_base_.updateArticles(rss_data);
    for (size_t i=0; i< rss_data.getArticlesSize(); ++i)
    {
         data_base_.insertIntoRssDataTable(rss_data.getSiteName()
                                 , rss_data.articleAt(i).getTitle()
                                 , rss_data.articleAt(i).getLink()
                                 , rss_data.articleAt(i).getText());
    }
}

void UpdateRssData::onDownloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (stateChanged("SettingsUpdated"));
    emit (stateChanged("RSSDataAdded"));
}

void UpdateRssData::makeConnections ()
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

void UpdateRssData::loadRssUrls()
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

void UpdateRssData::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    data_base_.removeAllDataFromRssData ();

    loadRssUrls();
    if (feeds_.size()>0)
    {
        //FIXME: (when thread_pool finished with init_main_window, it removes the pointer)
        download_rss_data_thread_ = new DownloadRssDataThread ();
        makeConnections();
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

void UpdateRssData::onUpdateSettings()
{
    qDebug()<<__PRETTY_FUNCTION__;
    loadRssUrls ();
    loadRssFeeds (); //start downloading of rss data
    //onUpdateRSSData
}

void UpdateRssData::onAddRssData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    onUpdateSettings ();
}

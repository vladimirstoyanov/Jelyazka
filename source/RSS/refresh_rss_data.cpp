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
    , network_manager_(std::make_shared<NetworkManager> ())
    , response_number_ (0)
    , time_msec_(60000) //1 minute
    , timer_ (std::make_shared<QTimer> ())
    , urls_size_ (0)
{
    setupConnections ();
}

RefreshRssData::~RefreshRssData()
{
    stop();
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
        QString html_source = "";
        generateHtmlSource(html_source);
        emit (rssDataUpdated(html_source));
    }
    new_articles_.clear();
    //loadRssFeeds();
    start(); //start the timer
}

void RefreshRssData::generateHtmlSource (QString &html_source)
{
    html_source = "";
    if (new_articles_.size() == 0)
    {
        return;
    }

    for (const RSSData &item: new_articles_)
    {
        html_source+="<a href = \""
                + item.articleAt(0).getLink()
                + "\" style=\"color: #000000\">"
                + item.getSiteName()
                + ": "
                + item.articleAt(0).getTitle()
                + "</a><br><hr>";
    }
}

void RefreshRssData::onTimeValueChanged(const int time_msec)
{
    this->time_msec_ = time_msec;
}

void RefreshRssData::onFavoriteFeedsChanged ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssData::writeData (const RSSData &rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;

    data_base_.updateArticles(rss_data, new_articles_);
}

void RefreshRssData::downloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void RefreshRssData::setupConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect( this
            , SIGNAL(httpGetRequest(const QString &))
            , network_manager_.get()
            , SLOT(onHttpGetRequest(const QString &))
            , Qt::QueuedConnection);

    connect( network_manager_.get()
            , SIGNAL(httpRequestReceived(const HttpData &))
            , this
            , SLOT(onHttpRequestReceived(const HttpData &))
            , Qt::QueuedConnection);

    connect( timer_.get(),
             SIGNAL(timeout()),
             this,
             SLOT(onTimeout()),
             Qt::QueuedConnection);
}

void RefreshRssData::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;
    std::vector<QString> urls;
    urls = data_base_.getURLs();
    urls_size_ = urls.size();
    response_number_ = 0;


    for (unsigned int i=0; i<urls_size_; ++i)
    {
        emit (httpGetRequest(urls[i]));
        qDebug()<<__PRETTY_FUNCTION__<<": after";
    }

    if (0 == urls_size_)
    {
        downloadFinished();
    }
}

void RefreshRssData::onHttpRequestReceived (const HttpData &httpData)
{
    ++response_number_;
    qDebug()<<__PRETTY_FUNCTION__<<"!!!!!!!!!!!!!!!!!!!!!";
    if (httpData.isResponseSuccessful())
    {
        ParseRSS parse;
        std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData> ();
        rss_data->setURL(httpData.getUrl());

        //pasrse web content to RSSData
        parse.getRSSDataByWebSource(httpData.getData(), rss_data);
        writeData(*rss_data.get());
    }
    if (response_number_ == urls_size_)
    {
        downloadFinished();
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

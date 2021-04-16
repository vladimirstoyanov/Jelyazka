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
    data_base_(),
    network_manager_(std::make_shared<NetworkManager> ()),
    response_number_ (0),
    urls_size_ (0)

{
    setupConnections ();
}

UpdateRssData::~UpdateRssData()
{
}

void UpdateRssData::writeData (const RSSData &rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;
    for (size_t i=0; i< rss_data.getArticlesSize(); ++i)
    {
         data_base_.insertIntoRssDataTable(rss_data.getSiteName()
                                 , rss_data.articleAt(i).getTitle()
                                 , rss_data.articleAt(i).getLink()
                                 , rss_data.articleAt(i).getText());
    }
}

void UpdateRssData::downloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (stateChanged("SettingsUpdated"));
    emit (stateChanged("RSSDataAdded"));
}

void UpdateRssData::setupConnections ()
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
}

void UpdateRssData::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    std::vector<QString> urls;
    urls = data_base_.getNewUrls();
    urls_size_ = urls.size();
    response_number_ = 0;
    for (const QString & item: urls)
    {
        emit (httpGetRequest(item));
        qDebug()<<__PRETTY_FUNCTION__<<": after";
    }

    if (0 == urls_size_)
    {
        downloadFinished();
    }
}

void UpdateRssData::onUpdateSettings()
{
    qDebug()<<__PRETTY_FUNCTION__;
    emit (stateChanged("SettingsUpdated"));
}

void UpdateRssData::onAddRssData ()
{
    qDebug()<<__PRETTY_FUNCTION__;
    loadRssFeeds ();
}

void UpdateRssData::onHttpRequestReceived (const HttpData &httpData)
{
    ++response_number_;
    qDebug()<<__PRETTY_FUNCTION__;
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

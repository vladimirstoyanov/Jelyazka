/*
    InitWindowThread.cpp
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
#include "init_window_thread.h"

Feed::Feed ()
    : feed_url_ ( "")
    , download_state_ (NONE)
{
}


InitWindowThread::InitWindowThread()
    : QRunnable()
{
}

InitWindowThread::~InitWindowThread()
{
}

void InitWindowThread::loadRssUrls()
{
    qDebug()<<__PRETTY_FUNCTION__<<" : loading RSS URLs from DB...";

    //get all URLs
    std::vector<QString> url_feeds;
    data_base_.getFeeds(&url_feeds);

    for (unsigned int i=0; i<url_feeds.size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<url_feeds[i];
        Feed feed;
        feed.setFeedUrl(url_feeds[i]);
        feeds_.push_back(feed);
    }
}

void InitWindowThread::run()
{
    qDebug()<<__PRETTY_FUNCTION__;

    int index = getFreeFeedIndex ();

    if (index<0)
    {
        //Everyone of the feeds is downloading now or it's downloaded
        return;
    }

    downloadFeed (index);
    if (isDownloadingFinished())
        ; //ToDo: emit signal to "InitWindow" that the RSS content has been downloaded
}

void InitWindowThread::downloadFeed (const unsigned int index)
{
     ParseRSS parserss;
     HTTP http;
     QString web_source;
     std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData>();

     rss_data->setURL(feeds_[index].getFeedUrl());

     //get the web content
     http.getQuery(feeds_[index].getFeedUrl(),web_source);

     //pasrse web content to RSSData
     parserss.getRSSDataByWebSource(web_source, rss_data);

     //write in data base

     feeds_[index].setDownloadState(DOWNLOADED);
}

int InitWindowThread::getFreeFeedIndex ()
{
    for (unsigned int i=0; i<feeds_.size(); i++)
    {
        if (feeds_[i].getDownloadState() == NONE)
        {
            feeds_[i].setDownloadState(DOWNLOADING);
            return i;
        }
    }
    return -1;
}

bool InitWindowThread::isDownloadingFinished ()
{
    for (unsigned int i=0; i<feeds_.size(); i++)
    {
        if (feeds_[i].getDownloadState()!=DOWNLOADED)
        {
            return false;
        }
    }
    return true;
}

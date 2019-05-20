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

    std::shared_ptr<Data> feeds = std::make_shared<Data> ();
    data_base_.loadStrctureFromDB(feeds);

    for (unsigned int i=0; i<feeds->size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<feeds->at(i)->getURL();
        Feed feed;
        feed.setFeedUrl(feeds->at(i)->getURL());
        feeds_.push_back(feed);
    }
}

void InitWindowThread::run()
{
    int index = getFreeFeedIndex ();
    qDebug()<<__PRETTY_FUNCTION__<<": index="<<index;

    if (index<0)
    {
        qDebug()<<__PRETTY_FUNCTION__<<": All feeds are downloading now or downloaded!";
        return;
    }

    downloadFeed (index);

    if (isDownloadingFinished())
    {
        qDebug()<<__PRETTY_FUNCTION__<<": It has been downloaded."; //ToDo: emit signal to "InitWindow" that the RSS content has been downloaded
    }
}

void InitWindowThread::downloadFeed (const unsigned int index)
{
     qDebug()<<__PRETTY_FUNCTION__;
     ParseRSS parserss;
     HTTP http;
     QString web_source;
     std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData>();

     rss_data->setURL(feeds_[index].getFeedUrl());

     //get the web content
     if (http.getQuery(feeds_[index].getFeedUrl(),web_source))
     {
         qDebug()<<__PRETTY_FUNCTION__<<": web content of "<<feeds_[index].getFeedUrl()<<" hasn't download!";
         feeds_[index].setDownloadState(DOWNLOADED);
         return;
     }

     //pasrse web content to RSSData
     parserss.getRSSDataByWebSource(web_source, rss_data);

     writeData(rss_data);

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

//write rss data to the data base
void InitWindowThread::writeData(std::shared_ptr<RSSData> rss_data)
{
    for (size_t i=0; i< rss_data->getArticlesSize(); ++i)
    {
         data_base_.insertIntoRssDataTable(rss_data->getSiteName()
                                 , rss_data->getTitle()
                                 , rss_data->getLink()
                                 , rss_data->articleAt(i).getText());
    }
}

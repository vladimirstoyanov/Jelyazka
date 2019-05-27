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
    : feed_url_ ("")
    , download_state_ (NONE)
{
}


InitWindowThread::InitWindowThread()
    : QRunnable()
{
}

InitWindowThread::~InitWindowThread()
{
    qDebug()<<__PRETTY_FUNCTION__;

}

void InitWindowThread::run()
{
    qDebug()<<__PRETTY_FUNCTION__;


    int index = getFreeFeedIndex ();

    qDebug()<<__PRETTY_FUNCTION__<<": index="<<index;

    if (index<0)
    {
        return;
    }

    downloadFeed (index);

    if (isDownloadingFinished())
    {
        emit downloadFinished ();
    }

}

void InitWindowThread::downloadFeed (const unsigned int index)
{
     qDebug()<<__PRETTY_FUNCTION__;
     ParseRSS parse;
     HTTP http;
     QString web_source;
     std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData> ();



     rss_data->setURL(feeds_[index].getFeedUrl());

     //get the web content
     if (http.getQuery(feeds_[index].getFeedUrl(),web_source))
     {
         qDebug()<<__PRETTY_FUNCTION__<<": web content of "<<feeds_[index].getFeedUrl()<<" hasn't download!";
         feeds_[index].setDownloadState(DOWNLOADED);
         return;
     }

     //pasrse web content to RSSData
     parse.getRSSDataByWebSource(web_source, rss_data);


     //ToDo: remove the below row. It has been added only for test reasons
     //test (rss_data);

     emit writeData (*rss_data.get());

     //ToDo: remove the below two rows. They have been added only for test reasons
     //rss_data->setSiteName("dnes.bg");
     //emit writeData (*rss_data.get());

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

void InitWindowThread::setURLs (std::vector<Feed> feeds)
{
    for (unsigned int i=0; i<feeds.size(); ++i)
    {
        feeds_.push_back(feeds[i]);
    }
}

void InitWindowThread::test (std::shared_ptr<RSSData> rss_data)
{
    rss_data->setSiteName("slashdot");
    rss_data->setVersion("2005");
    rss_data->setEncoding("UTF-8");
    for (unsigned int i = 0; i<10; ++i)
    {
        RSSArticle rss_article;

        rss_article.setLink ("link "     + QString::number(i));
        rss_article.setText ("text "     + QString::number(i));
        rss_article.setTitle("title "    + QString::number(i));
        rss_article.setDate ("date "     + QString::number(i));
        rss_data->articlesPushBack(rss_article);
    }
}

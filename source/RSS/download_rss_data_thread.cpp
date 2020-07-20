/*
    DownloadRssDataThread.cpp
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
#include "download_rss_data_thread.h"

#include <unistd.h>

Feed::Feed ()
    : feed_url_ ("")
    , download_state_ (NONE)
{
}


DownloadRssDataThread::DownloadRssDataThread()
    : QRunnable(),
      network_manager_(std::make_shared<NetworkManager> ())
{
    setupConnections();
}

DownloadRssDataThread::~DownloadRssDataThread()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void DownloadRssDataThread::run()
{
    qDebug()<<__PRETTY_FUNCTION__;

    int index = getFreeFeedIndex ();

    qDebug()<<__PRETTY_FUNCTION__<<": index="<<index;

    if (index<0)
    {
        return;
    }

    downloadFeed (index);

    //FIXME
    while (feeds_[index].getDownloadState() != DOWNLOADED)
    {
        usleep(10000);
    }

    if (isDownloadingFinished())
    {
        qDebug()<<__PRETTY_FUNCTION__<<": download has been finished.";
        emit (downloadFinished());
    }
    qDebug()<<__PRETTY_FUNCTION__<<" finished";

}

void DownloadRssDataThread::downloadFeed (const unsigned int index)
{
     qDebug()<<__PRETTY_FUNCTION__;
     network_manager_->getHttpRequest(feeds_[index].getFeedUrl());
}

int DownloadRssDataThread::getFreeFeedIndex ()
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

bool DownloadRssDataThread::isDownloadingFinished ()
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

void DownloadRssDataThread::setURLs (std::vector<Feed> const &feeds)
{
     for (unsigned int i=0; i<feeds.size(); ++i)
    {
        feeds_.push_back(feeds[i]);
    }
}

void DownloadRssDataThread::test (std::shared_ptr<RSSData> rss_data)
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

void DownloadRssDataThread::setFeedStateToDownloaded (const QString &url)
{
    qDebug()<<__PRETTY_FUNCTION__;
    for (unsigned int i=0; i<feeds_.size(); ++i)
    {
        if (url == feeds_[i].getFeedUrl())
        {
            feeds_[i].setDownloadState(DOWNLOADED);
            break;
        }
    }
}

void DownloadRssDataThread::onHttpRequestReceived (const HttpData httpData)
{
    qDebug()<<__PRETTY_FUNCTION__<<"!!!!!!!!!!!!!!!!!!!!!";
    if (httpData.isResponseSuccessful())
    {
        ParseRSS parse;
        std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData> ();
        rss_data->setURL(httpData.getUrl());

        //pasrse web content to RSSData
        parse.getRSSDataByWebSource(httpData.getData(), rss_data);

        emit writeData (*rss_data.get());
    }
    setFeedStateToDownloaded(httpData.getUrl());
}

void DownloadRssDataThread::setupConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__<<"!!!!!!!!!!!!!!";
    connect( network_manager_.get()
            , SIGNAL(httpRequestReceived(const HttpData))
            , this
            , SLOT(onHttpRequestReceived(const HttpData))
            , Qt::QueuedConnection);

}

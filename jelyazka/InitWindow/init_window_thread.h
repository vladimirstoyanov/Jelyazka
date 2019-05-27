/*
    init_window_thread.h
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
#ifndef INITWINDOWTHREAD_H
#define INITWINDOWTHREAD_H

#include <memory>
#include <vector>

#include <QRunnable>
#include <QtDebug>

#include "http.h"
#include "RSS/parserss.h"

enum DownloadState
{
    NONE,
    DOWNLOADING,
    DOWNLOADED
};

class Feed
{
public:
    Feed ();
    void setFeedUrl         (const QString &feed_url) { this->feed_url_ = feed_url; }
    void setDownloadState   (const DownloadState download_state) {this->download_state_ = download_state; }

    QString getFeedUrl              () const { return this->feed_url_;}
    DownloadState getDownloadState  () const { return this->download_state_;}
private:
    QString feed_url_;
    DownloadState    download_state_;
};

class InitWindowThread : public QObject, public QRunnable
{
    Q_OBJECT

public:
    InitWindowThread();
    virtual ~InitWindowThread();

    unsigned int getFeedsCount  () const { return this->feeds_.size(); }
    void         run            ();
    void         setURLs        (std::vector<Feed> feeds);

private:
        std::vector<Feed>       feeds_;

private:
       bool isDownloadingFinished();
       void downloadFeed (const unsigned int index);
       int  getFreeFeedIndex ();
       void test (std::shared_ptr<RSSData> rss_data);

signals:
       void downloadFinished();
       void writeData (RSSData rss_data);
};

#endif // INITWINDOWTHREAD_H

/*
    rssthread.h
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
#ifndef REFRESHRSSDATATIMER_H
#define REFRESHRSSDATATIMER_H

#include <memory>

#include <QObject>
#include <QtDebug>
#include <QThreadPool>
#include <QTimer>

#include "database.h"
#include "InitWindow/init_window_thread.h"

class RefreshRssDataTimer : public QObject
{
    Q_OBJECT
public:
    RefreshRssDataTimer();
    virtual ~RefreshRssDataTimer();

    void start ();
    void stop  ();

public slots:
    void onDownloadFinished ();
    void onFavoriteFeedsChanged ();
    void onStartRssRefreshData ();
    void onStopRssRefreshData ();
    void onTimeout();
    void onTimeValueChanged (const int time_msec);
    void onWriteData (const RSSData rss_data);

signals:
    void rssDataUpdated (std::vector<RSSData>);

private:
    DataBase                        data_base_;
    std::vector<Feed>               feeds_;
    InitWindowThread*               init_window_thread_;
    std::vector<RSSData>            new_articles_;
    std::shared_ptr<QThreadPool>    thread_pool_;
    int                             time_msec_;
    std::shared_ptr<QTimer>         timer_;


private:
   void makeConnections ();
   void loadRssFeeds();
   void loadRssUrls ();
};

#endif // REFRESHRSSDATATIMER_H

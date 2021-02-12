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
#include "Network/network_manager.h"
#include "rss_data.h"
#include "RSS/parse_rss.h"
#include "settings.h"


class RefreshRssData : public QObject
{
    Q_OBJECT
public:
    RefreshRssData();
    virtual ~RefreshRssData();

    void start ();
    void stop  ();

public slots:
    void onFavoriteFeedsChanged ();
    void onStartRssRefreshData ();
    void onStopRssRefreshData ();
    void onTimeout();
    void onTimeValueChanged (const int time_msec);

signals:
    void httpGetRequest (const QString &);
    void rssDataUpdated (std::vector<RSSData>);

private slots:
    void onHttpRequestReceived (const HttpData httpData);

private:
    DataBase                            data_base_;
    std::vector<RSSData>                new_articles_;
    std::shared_ptr<NetworkManager>     network_manager_;
    unsigned int                        response_number_;
    std::shared_ptr<QThreadPool>        thread_pool_;
    int                                 time_msec_;
    std::shared_ptr<QTimer>             timer_;
    unsigned int                        urls_size_;


private:
   void downloadFinished ();
   void setupConnections ();
   void loadRssFeeds();
   void writeData (const RSSData rss_data);

};

#endif // REFRESHRSSDATATIMER_H

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
#ifndef UpdateRssData_H
#define UpdateRssData_H

#include <memory>

#include <QObject>
#include <QtDebug>
#include <QThreadPool>

#include "database.h"
#include "Network/network_manager.h"
#include "rss_data.h"
#include "RSS/parse_rss.h"


class UpdateRssData : public QObject
{
    Q_OBJECT
public:
    UpdateRssData();
    virtual ~UpdateRssData();

public slots:
    void onAddRssData ();
    void onDownloadFinished ();
    void onWriteData (const RSSData &rss_data);
    void onUpdateSettings();

signals:
    void httpGetRequest (const QString &);
    void stateChanged (const QString &);

private slots:
    void onHttpRequestReceived (const HttpData httpData);

private:
    DataBase                        data_base_;
    std::shared_ptr<NetworkManager> network_manager_;
    unsigned int                    response_number_;
    unsigned int                    urls_size_;


private:
   void makeConnections ();
   void loadRssFeeds();
   void loadRssUrls ();
};

#endif // UpdateRssData_H

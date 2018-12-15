/*
    refreshfeedsdata.cpp
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
#include "refreshfeedsdata.h"

RefreshFeedsData::RefreshFeedsData(QObject *parent, RSSThread *rss_thread, Data *data) :
    QThread(parent)
{
    rss_thread_ = rss_thread;
    data_ = data;
}

RefreshFeedsData::~RefreshFeedsData()
{
}

void RefreshFeedsData::run() //refresh feeds
{
    HTTP http;
    QString content;

    while (1)
    {
        qDebug()<<"run():Before sleep...";
        int t = rss_thread_->getRefreshTime();
        msleep(t*60000);
        qDebug()<<"run():After sleep...";

        rss_thread_->data_for_animatewindow_ = "";
        int n = data_->size();


        for (unsigned int i=0; i<n; i++)
        {
            content="";
            qDebug()<<"Trying to refresh in RefreshFeedsData, index: " + QString::number(i);

            if (data_->size()<=i)
            {
                qDebug()<<"site_struct->s_struct.size()<=i";
                break;
            }
            QString url = data_->at(i)->getURL();
            if (http.getQuery(url,content))
            {
                qDebug()<<"Fail to connect: "<<url;
                continue;
            }

            qDebug()<<"Download data in RefreshFeedsData, index: " + QString::number(i);

            if (data_->size()<=i)
            {
                qDebug()<<"site_struct->s_struct.size()<=i";
                break;
            }
            rss_thread_->synchronizeData(i,content);
            qDebug()<<"Synchronize data in RefreshFeedsData, index: " + QString::number(i);
        }
        if (rss_thread_->getEnabledNotificationWindow())
        {
            qDebug()<<"Emit animate window";
            rss_thread_->emitAnimateWindow();
        }
    }
    exec();
}

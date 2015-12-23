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
#include <QDebug>

RefreshFeedsData::RefreshFeedsData(QObject *parent, RSSThread *ss, Data *data_tmp) :
    QThread(parent)
{
    site_struct = ss;
    data = data_tmp;
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
        int t = site_struct->getRefreshTime();
        msleep(t*60000);
        qDebug()<<"run():After sleep...";

        site_struct->data_for_animatewindow = "";
        int n = data->size();


        for (int i=0; i<n; i++)
        {
            content="";
            qDebug()<<"Trying to refresh in RefreshFeedsData, index: " + QString::number(i);

            if (data->size()<=i)
            {
                qDebug()<<"site_struct->s_struct.size()<=i";
                break;
            }
            QString url = data->at(i)->getURL();
            if (http.getQuery(url,content))
            {
                qDebug()<<"Fail to connect: "<<url;
                continue;
            }

            qDebug()<<"Download data in RefreshFeedsData, index: " + QString::number(i);

            if (data->size()<=i)
            {
                qDebug()<<"site_struct->s_struct.size()<=i";
                break;
            }
            site_struct->synchronizeData(i,content);
            qDebug()<<"Synchronize data in RefreshFeedsData, index: " + QString::number(i);
        }
        if (site_struct->getEnabledNotificationWindow())
        {
            qDebug()<<"Emit animate window";
            site_struct->emitAnimateWindow();
        }
    }
    exec();
}

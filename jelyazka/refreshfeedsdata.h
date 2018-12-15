/*
    refreshfeedsdata.h
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
#ifndef REFRESHFEEDSDATA_H
#define REFRESHFEEDSDATA_H

#include <QDebug>
#include <QMutex>
#include <QThread>

#include "data.h"
#include "rssthread.h"

class RefreshFeedsData : public QThread
{
    Q_OBJECT
public:
    explicit RefreshFeedsData(QObject *parent = 0, RSSThread *rss_thread=0, Data *data=0);
    virtual ~RefreshFeedsData();

public:
    void run();

private:
    RSSThread *rss_thread_;
    Data *data_;
};

#endif // REFRESHFEEDSDATA_H

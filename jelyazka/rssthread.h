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
#ifndef RSSTHREAD_H
#define RSSTHREAD_H

//#include <boost/ptr_container/ptr_vector.hpp>

#include <fstream>
#include <limits.h>
#include <memory>
#include <string>
#include <vector>

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMutex>
#include <QNetworkProxy>
#include <QString>
#include <QStringList>
#include <QtCore>
#include <QTextCodec>
#include <QTextStream>
#include <QThreadPool>
#include <QWaitCondition>

#include "data.h"
#include "database.h"
#include "http.h"
#include "notificationwindow.h"
#include "parserss.h"

class AnimateWindow;

class RSSThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    //move the bellow members to private section
    bool first_load_;
    bool is_add_option_;
    QNetworkProxy *network_proxy_;
    bool enabled_proxy_connection_;
    bool enabled_notification_window_;
    bool enabled_filters_;
    bool busy_;
    QString proxy_url_;
    QString proxy_port_;
    QString data_for_animatewindow_;
    QWaitCondition condition_tread_;
    QWaitCondition condition_view_;
    
    RSSThread(std::shared_ptr<Data> data);
    virtual ~RSSThread();

    void emitAnimateWindow();
    void setProxySettings();
    void setRefreshTime(int refresh_time_feeds);
    void setEnableNotificationWindow(bool enabled_notification_window);
    void synchronizeData(int site_index, QString content);

public:
    void run (); //function exec when a thread start

public:
    bool getEnabledNotificationWindow();
    int getRefreshTime();
    std::shared_ptr<RSSData>  initStruct(QString site_name, QString type, QString url);

signals:
    void loadRSS(QString name, QString url); //signal load rss feed
    void showAnimateWindow(QString data); //anitate window signal
    //ToDO: rename the below funtion
    void Finish(QString name, bool finish); //signal to option, when add rss feeds from 'collect' to 'view'

private:
    int checkIsLoaded();
    void loadOptions();

private:
    std::shared_ptr<QMutex> mutex_; //using for threads
    bool is_first_flag_;
    std::shared_ptr<QThreadPool> thread_pool_;
    int refresh_time_feeds_;
    DataBase data_base_;
    std::shared_ptr<Data> data_;
    std::shared_ptr<ParseRSS> parse_rss_;
};

#endif // RSSTHREAD_H

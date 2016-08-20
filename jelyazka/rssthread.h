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

#include "notificationwindow.h"
#include <QtCore>
#include <QThreadPool>
#include <QDebug>
#include <fstream>
#include <string>
#include <QString>
#include <QMutex>
#include "http.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QStringList>
#include <boost/ptr_container/ptr_vector.hpp>
#include <QWaitCondition>
#include <QTextCodec>
#include "database.h"
#include "data.h"
#include <limits.h>
#include "parserss.h"


class AnimateWindow;

class RSSThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
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
    
    RSSThread(Data *data);
    ~RSSThread();

    //boost::ptr_vector<RSSData> s_struct; //vector with all rss data

    RSSData * initStruct(QString site_name, QString type, QString url);
    void synchronizeData(int site_index, QString content);
    void run (); //function exec when thread start
    int getRefreshTime()
    {
        return refresh_time_feeds_;
    }
    void setRefreshTime(int refresh_time_feeds)
    {
        refresh_time_feeds_ = refresh_time_feeds;
    }
    void setEnableNotificationWindow(bool enabled_notification_window)
    {
        enabled_notification_window_ = enabled_notification_window;
    }
    void setProxySettings();
    bool getEnabledNotificationWindow()
    {
        return enabled_notification_window_;
    }
    void emitAnimateWindow();

signals:
    void showAnimateWindow(QString data); //anitate window signal
    void loadRSS(QString name, QString url); //signal load rss feed
    void Finish(QString name, bool finish); //signal to option, when add rss feeds from 'collect' to 'view'

private:
    QMutex *mutex_; //using for threads
    bool first_flag_;
    QThreadPool *thread_pool_;
    int refresh_time_feeds_;
    DataBase data_base_;
    Data *data_;
    ParseRSS *parse_rss_;

    void loadOptions();
    int checkIsLoaded();
};

#endif // RSSTHREAD_H

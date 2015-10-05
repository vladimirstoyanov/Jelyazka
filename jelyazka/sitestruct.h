/*
    sitestruct.h
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
#ifndef SITESTRUCT_H
#define SITESTRUCT_H

#include "animatewindow.h"
#include <QtCore>
#include <QThreadPool>
#include <QDebug>
#include <QtSql/QtSql>
#include <fstream>
#include <string>
#include <QString>
#include <QMutex>
#include "net.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QStringList>
#include <boost/ptr_container/ptr_vector.hpp>
#include <QWaitCondition>
#include <QTextCodec>

#define INT_SIZE 2147483646

class CAnimateWindow;

class SiteStruct : public QObject, public QRunnable
{
    Q_OBJECT
public:
    bool first_load;
    bool isAddOption;
    QNetworkProxy *network_proxy;
    bool enabled_proxy_connection;
    bool enabled_notification_window;
    bool busy;
    QString proxy_url;
    QString proxy_port;
    QString data_for_animatewindow;
    QWaitCondition condition_tread;
    QWaitCondition condition_view;
    
    SiteStruct(QObject *parent);
    ~SiteStruct();
    QSqlDatabase sqliteDataBase;

    struct article //article struct
    {
        QString title; //title of article
        QString link;
        QString text;
        article()
        {
            title=""; //init
            link="";
            text ="";
        }
    }art;

    struct site_struct{
        QString type;
        QString site_name;
        QString url;
        QString encoding;
        QString version;
        bool isRead;
        bool isLoaded;
        //boost::ptr_list<article> articles; //new
        QList<article> articles;
        site_struct(){
            site_name= "";
            url= "";
            type ="";
            encoding = "";
            isRead = false;
            isLoaded = false;
            version = "0";
        }
    };
    boost::ptr_vector<site_struct> s_struct;
    //QList<site_struct> s_struct;

    void loadStrctureFromDB(); //load settings in sites.obj
    site_struct * initStruct(QString site_name, QString type, QString url);
    void synchronizeData(int site_index, QString content);
    void run (); //function exec when thread start
    int getRefreshTime(){return refresh_time_feeds;}
    void setRefreshTime(int refresh_time_feeds_tmp){refresh_time_feeds = refresh_time_feeds_tmp;}
    void setEnableNotificationWindow(bool enabled_notification_window_tmp){enabled_notification_window = enabled_notification_window_tmp;}
    void setProxySettings();
    bool getEnabledNotificationWindow(){return enabled_notification_window;}
    void emitAnimateWindow();
    int getTextBetweenIndexes(int item_b_index, int item_e_index, QString begin_text, QString end_text, QString &text, QString content);
    int getDescription(int item_b_index, int item_e_index, QString &description, QString content);
    QString convert_entitie(QString entitie);
    void convert_string (QString &str, bool link);
    QString returnURL(QString source, int index);
    int getContent(int item_b_index, int item_e_index, QString &description, QString content);

signals:
    void showAnimateWindow(QString data); //anitate window signal
    void loadRSS(QString name, QString url); //signal load rss feed
    //void addRSS(QString name, bool finish); //signal load rss feed
    void Finish(QString name, bool finish); //signal to option, when add rss feeds from 'collect' to 'view'

private:
    QMutex *mutex; //using for threads
    bool first_flag;
    QThreadPool *tp;
    int refresh_time_feeds;

    void createTables();
    void loadOptions();
    void findSiteDataRSS(int &index, QString content, QString &title, QString &link, QString &text);
    void findSiteDataRSS2(int &index, QString content, QString &title, QString &link, QString &text);
    int getArticlesForIndexRSS(QString content,uint struct_index);
    int getArticlesForIndexRSS2(QString content,uint struct_index);
    int checkIsLoaded();
};

#endif // SITESTRUCT_H

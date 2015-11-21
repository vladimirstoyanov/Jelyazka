/*
    web_search_interface_thread.h
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
#ifndef WEB_SEARCH_INTERFACE_THREAD_H
#define WEB_SEARCH_INTERFACE_THREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <QRunnable>
#include <QMutex>
#include <QList>
#include <boost/ptr_container/ptr_list.hpp>
#include "logger.h"
#include "db.h"

class WebSearchInterfaceThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    boost::ptr_list<QString> l_url;
    boost::ptr_list<QString> l_url2;
    QList<int> l_flags;


    explicit WebSearchInterfaceThread();

    ~WebSearchInterfaceThread();
    void run();
    QMutex *mutex;

    bool stop_thread;

    int checkUrl(QString url, QString source);
    void getUrl (QString html_source, int &index, QString &return_url);
    int checkListForExistUrl(QString url);
    void buildUrl (QString url_root, QString url, QString &return_url);
    int checkForRss(QString source, QString &title, int &version);
    int lookForHref(QString source, int &index);
    void addOrRemoveLastSymbolSlash(QString url, QString *new_url);
    int checkForRootURL(QString url, int i, int i1);
    int deleteAllFrom_all_url_table();
    int insertUrlDB(QString url);
    int findUrlDB(QString url);
    bool setUrlRoot(QString url);
    int fixProtocol(QString &url);

private:
    Logger log;
    QString url_root;
    DB db;
    QString getEncodingFromRSS(QString content);
    void allURLVariants(QString url);
    void addOrRemoveWWW(QString url, QString *new_url);
    int checkFinish();



signals:
    void FoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version);
    void EndOfUrls();
public slots:

};

#endif // WEB_SEARCH_INTERFACE_THREAD_H

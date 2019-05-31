/*
    rsssearchthread.h
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


#include <memory>

#include <QList>
#include <QMutex>
#include <QRunnable>
#include <QString>
#include <QThread>

#include "database.h"
#include "logger.h"

class RSSSearchGUIThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    std::vector<QString> l_url;
    std::vector<QString> l_url2;
    QList<int> l_flags;
    std::shared_ptr<QMutex> mutex;
    bool stop_thread;

    explicit RSSSearchGUIThread();
    virtual ~RSSSearchGUIThread();

public:
    void run();

public:
    void addOrRemoveLastSymbolSlash(QString url, QString *new_url);
    void buildUrl (QString url_root, QString url, QString &return_url);
    void getUrl (QString html_source, int &index, QString &return_url);

public:
    bool setUrlRoot(QString url);
    int checkForRootURL(QString url, int i, int i1);
    int checkForRss(QString source, QString &title, int &version);
    int checkListForExistUrl(QString url);
    int checkUrl(QString url, QString source);
    int deleteAllFrom_all_url_table();
    int fixProtocol(QString &url);
    int findUrlDB(QString url);
    int insertUrlDB(QString url);
    int lookForHref(QString source, int &index);

private:
    Logger log_;
    QString url_root_;
    DataBase data_base_;
    QString getEncodingFromRSS(QString content);
    void allURLVariants(QString url);
    void addOrRemoveWWW(QString url, QString *new_url);
    int checkFinish();

signals:  
    void EndOfUrls();
    void FoundRSS(int type,
                  QString name,
                  QString url,
                  QString encoding,
                  QString web_source,
                  int version);
};

#endif // WEB_SEARCH_INTERFACE_THREAD_H

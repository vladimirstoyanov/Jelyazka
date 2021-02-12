/*
    rss_searcht_hread.h
    Jelyazka RSS/RDF reader
    Copyright (C) 2020 Vladimir Stoyanov

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
#include <queue>
#include <unistd.h>

#include <QList>
#include <QThread>
#include <QString>
#include <QThread>

#include "database.h"
#include "logger.h"
#include "Network/network_manager.h"


class RSSSearchGUIThread : public QThread
{
     Q_OBJECT
public:
    explicit RSSSearchGUIThread();
    virtual ~RSSSearchGUIThread();

private:
    std::queue<QString>         url_queue_;
    int                         pending_urls_;
    bool                        stop_thread_;

public:
    void run();

public:
    void    setInitialUrl (const QString & url);
    void    stopThread ();
    void    addOrRemoveLastSymbolSlash  (const QString &url, QString *new_url);
    void    buildUrl                    (const QString &url_root, const QString &url, QString &return_url);
    int     checkForRootURL             (const QString &url, int i, int i1);
    int     checkForRss                 (const QString &source, QString &title, int &version);
    int     checkListForExistUrl        (const QString &url);
    int     checkUrl                    (const QString &url, const QString &source);
    int     deleteAllFrom_all_url_table ();
    int     fixProtocol                 (QString &url);
    int     findUrlDB                   (const QString &url);
    void    getUrl                      (const QString &html_source, int &index, QString &return_url);
    int     insertUrlDB                 (const QString &url);
    int     lookForHref                 (const QString &source, int &index);
    bool    setUrlRoot                  (QString url); //this method changes url variable
    void    setupConnections            ();

private:
    DataBase    data_base_;
    bool        is_search_finished_; //FIXME
    std::shared_ptr<NetworkManager> network_manager_;
    Logger      log_;
    QString     url_root_;

private:
    void    addOrRemoveWWW          (const QString &url, QString *new_url);
    void    allURLVariants          (const QString &url);
    QString getEncodingFromRSS      (const QString &content);

public slots:
    void onHttpRequestReceived(const HttpData);
signals:
    void changeUrlLabel (const QString &url);
    void endOfUrls      ();
    void foundRSS       (const QString &name,
                         const QString &url,
                         const QString &encoding,
                         const QString &web_source,
                         const int version);
    void httpGetRequest (const QString &);
};

#endif // WEB_SEARCH_INTERFACE_THREAD_H

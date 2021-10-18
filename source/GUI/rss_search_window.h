/*
    rsssearchgui.h
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
#ifndef WEB_SEARCH_INTERFACE_H
#define WEB_SEARCH_INTERFACE_H

#include <limits.h>
#include <map>
#include <memory>

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QFontMetrics>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMutex>
#include <QWidget>
#include <QResizeEvent>
#include <QSize>
#include <QStandardItemModel>
#include <QString>
#include <QtCore>
#include <QTableView>
#include <QTextCodec>

#include "Network/http.h"
#include "logger.h"
#include "RSS/parse_rss.h"
#include "RSS/rss_search_thread.h"
#include "search.h"
#include "ui_rsssearchgui.h"

namespace Ui
{
    class RSSSearchGUI;
}

class RSSSearchGUI : public QWidget
{
    Q_OBJECT

public:
    explicit RSSSearchGUI(QWidget *parent = nullptr);
    virtual ~RSSSearchGUI();

public slots:
    void onChangeUrlLabel (QString url);
    void onEndOfUrls();
    void onFoundRSS(QString name
                    , const QString &url
                    , const QString &encoding
                    , const QString &web_source
                    , const int version);

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);

private:
    int                                             add_id_;
    DataBase                                        data_base_;
    int                                             encoding_id_;
    std::shared_ptr<QGridLayout>                    grid_;
    std::shared_ptr<QStandardItemModel>             model_;
    int                                             name_id_;
    std::shared_ptr<ParseRSS>                       parse_rss_;
    std::map <QString, std::shared_ptr<RSSData >>   rss_data_;
    RSSSearchGUIThread                              *rss_search_thread_;
    std::shared_ptr<Ui::RSSSearchGUI>               ui_;
    int                                             url_id_;

    void                     closeEvent(QCloseEvent *);
    bool                     isUrlExist(const QString &url);
    void                     convertUppercaseToLowercase(QString &url);
    QString                  getEncodingFromRSS(const QString &content);
    QString                  insertName(const QString &name);
    bool                     isRssFeedChecked(const QString &url);
    void                     modifyStringToFitWindowSize(QString &str);
    void                     paintRows();
    void                     removeRssData (const QString &name);
    void                     setRssFeeds (const QString &web_source, std::shared_ptr<RSSData> rss_data);
    void                     setupGui ();

private slots:
    //ToDo: rename the below functions
    void on_addRssFeeds_clicked(); //"add RSS feeds" button
    void on_removeButton_clicked(); //'Remove' button clicked
    void on_searchButton_clicked(); //'Search' button

signals:
    void stateChanged (const QString &);
};

#endif // WEB_SEARCH_INTERFACE_H

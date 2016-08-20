/*
    optionswindow.h
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
#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H


#include <QWidget>
#include <QListWidget>
#include <QResizeEvent>
#include <QThreadPool>
#include <QTextEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <boost/ptr_container/ptr_vector.hpp>
#include "rssthread.h"
#include "viewwindow.h"
#include "http.h"
#include "database.h"
#include "data.h"

namespace Ui {
class OptionsWindow;
}

class ViewWindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0, RSSThread *ss=0, ViewWindow *view_window=0, Data *data_tmp = 0);
    ~OptionsWindow();

public slots:
    void onFinish(QString name, bool finish);

private slots:
    void on_pushButton_clicked(); //'Remove' button clicked
    void on_pushButton_2_clicked(); // '<<' button clicked
    void on_OK_Button_clicked(); //'OK' button clicked
    void on_Cancel_Button_clicked(); //'Cancel' button clicked
    void on_pushButton_3_clicked(); // '>>' button clicked
    void on_collect_feeds_DoubleClicked(QListWidgetItem*);

    void on_treeWidget_clicked(const QModelIndex &index);
    void on_cb_enable_proxy_clicked(bool);
    void on_cb_enable_filtering_clicked(bool);
    void on_pb_add_filter_clicked();
    void on_pb_remove_filter();
    void on_textChanged(QString text);

private:
    DataBase db;
    Ui::OptionsWindow *ui;
    RSSThread *site_struct;
    Data *data;
    QListWidget *collect_feeds;
    QListWidget *view_feeds;
    boost::ptr_vector<QString> l_old_collect_feed;
    boost::ptr_vector<QString> l_old_view_feed;
    boost::ptr_vector<QString> l_old_filters;
    int options_type;
    QThreadPool *tp;
    QList<bool> l_items_for_remove;
    ViewWindow *vw;
    QLabel *download_feed_status;

    QLineEdit *cf_find_feed;
    QLabel *cf_label_search;

    //QTextEdit *te_refresh_time;
    QLabel *l_refresh_time;
    QCheckBox *cb_enable_notification;
    QSpinBox *sb_refresh_time;

    QLabel *l_proxy_url;
    QLabel *l_proxy_port;
    QTextEdit *te_proxy_url;
    QTextEdit *te_proxy_port;
    QCheckBox *cb_enable_proxy;

    //filter options widgets
    QPushButton *pb_add_filter;
    QTextEdit *te_add_filter;
    QListWidget *lw_filter_list;
    QLabel *l_filter_list;
    QPushButton *pb_remove_filter;
    QCheckBox *cb_enable_filtering;


    void showEvent(QShowEvent *);

    //show widgets
    void showCollectionFeeds();
    void showFilters();
    void showNotifications();
    void showProxyConnection();
    //hide widgets
    void hideCollectionFeeds();
    void hideFilters();
    void hideNotifications();
    void hideProxyConnection();

    void resizeEvent(QResizeEvent *event);
    void addItem(QString name);
    void fillCollectListView();
    void fillFilterListView();
    int addStringToWatchList(QString str);
    void fillViewListView();
    int addStringToViewList(QString str);
    void rssTableUpdate();
    void collect_feedsTableUpdate();
    void removeDataFromRSSTable(QString site_name, bool all_data);
    void removeDataFromCollectFeeds(QString site_name);
    void insertRowToRSSTable(QString site_name, QString url, QString version);
    void insertRowToFiltersTable(QString filter_name);
    void removeDataFromFilters(QString filter_name, bool all_data);
    int addStringToFilterList(QString cur_text);
    void returnModifedString(QString &str);
    void findAndReturnURLAndVersion(QString site_name, QString &url, QString &version);
    void updateFiltersTable();
    void loadOptions();
    void saveOptions();
    void updateCollectFeedListView();
    int cf_label_search_width();
};
#endif // OPTIONSWINDOW_H

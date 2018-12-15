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

#include <boost/ptr_container/ptr_vector.hpp>
#include <QCheckBox>
#include <QLineEdit>
#include <QListWidget>
#include <QResizeEvent>
#include <QSpinBox>
#include <QTextEdit>
#include <QThreadPool>
#include <QWidget>

#include "data.h"
#include "database.h"
#include "mainwindow.h"
#include "http.h"
#include "rssthread.h"

namespace Ui {
class OptionsWindow;
}

class MainWindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = 0, RSSThread *rss_thread=0, Data *data = 0);
    ~OptionsWindow();

public slots:
    void onFinish(QString name, bool finish);

private slots:
    //ToDo: rename button names
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
     void resizeEvent(QResizeEvent *event);
     void showEvent(QShowEvent *);
private:
    void addItem(QString name);
    void collect_feedsTableUpdate(); //ToDo: change the funtion name
    void fillCollectListView();
    void fillFilterListView();
    void fillViewListView();
    void insertRowToRSSTable(QString site_name, QString url, QString version);
    void insertRowToFiltersTable(QString filter_name);
    void rssTableUpdate();
    void removeDataFromCollectFeeds(QString site_name);
    void removeDataFromFilters(QString filter_name, bool all_data);
    void removeDataFromRSSTable(QString site_name, bool all_data);
    void returnModifedString(QString &str); //ToDo: change the function name
    void updateCollectFeedListView();
    void updateFiltersTable();
private:
    void loadOptions();
    void saveOptions();

private:
    //hide widgets
    void hideCollectionFeeds();
    void hideFilters();
    void hideNotifications();
    void hideProxyConnection();
    //show widgets
    void showCollectionFeeds();
    void showFilters();
    void showNotifications();
    void showProxyConnection();

private:
    int addStringToFilterList(QString cur_text);
    int addStringToWatchList(QString str);
    int addStringToViewList(QString str);
    int cf_label_search_width(); //ToDo: change the function name
















private:
    DataBase data_base_;
    Ui::OptionsWindow *ui_;
    RSSThread *rss_thread_;
    Data *data_;
    QListWidget *collect_feeds_;
    QListWidget *view_feeds_;
    boost::ptr_vector<QString> l_old_collect_feed_;
    boost::ptr_vector<QString> l_old_view_feed_;
    boost::ptr_vector<QString> l_old_filters_;
    int options_type_;
    QThreadPool *thread_pool_;
    QList<bool> l_items_for_remove_;
    MainWindow *main_window_;
    QLabel *download_feed_status_;

    QLineEdit *cf_find_feed_;
    QLabel *cf_label_search_;

    //QTextEdit *te_refresh_time;
    QLabel *l_refresh_time_;
    QCheckBox *cb_enable_notification_;
    QSpinBox *sb_refresh_time_;

    QLabel *l_proxy_url_;
    QLabel *l_proxy_port_;
    QTextEdit *te_proxy_url_;
    QTextEdit *te_proxy_port_;
    QCheckBox *cb_enable_proxy_;

    //filter options widgets
    QPushButton *pb_add_filter_;
    QTextEdit *te_add_filter_;
    QListWidget *lw_filter_list_;
    QLabel *l_filter_list_;
    QPushButton *pb_remove_filter_;
    QCheckBox *cb_enable_filtering_;


};
#endif // OPTIONSWINDOW_H

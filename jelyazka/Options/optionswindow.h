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

#include <memory>
#include <vector>

#include <QCheckBox>
#include <QCloseEvent>
#include <QDebug>
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
#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class MainWindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsWindow(
            QWidget *parent = nullptr
            , std::shared_ptr<RSSThread> rss_thread = nullptr
            , std::shared_ptr<Data> data = nullptr);

    ~OptionsWindow();

public slots:
    void onFinish(const QString &name, const bool finish);

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
    void on_textChanged(const QString &text);

private:
     void closeEvent(QShowEvent *);
     void resizeEvent(QResizeEvent *event);
     void showEvent(QShowEvent *);
private:
    void addItem(const QString &name);
    void collect_feedsTableUpdate(); //ToDo: change the funtion name
    void fillCollectListView();
    void fillFilterListView();
    void fillViewListView();
    void insertRowToRSSTable(const QString &site_name, const QString &url, const QString &version);
    void insertRowToFiltersTable(const QString &filter_name);
    void rssTableUpdate();
    void removeDataFromCollectFeeds(const QString &site_name);
    void removeDataFromFilters(const QString &filter_name, const bool all_data);
    void removeDataFromRSSTable(const QString &site_name, const bool all_data);
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
    int addStringToFilterList(const QString &cur_text);
    int addStringToWatchList(const QString &str);
    int addStringToViewList(const QString &str);
    int cf_label_search_width(); //ToDo: change the function name

private:
    DataBase data_base_;
    std::shared_ptr<Ui::OptionsWindow> ui_;
    std::shared_ptr<RSSThread> rss_thread_;
    std::shared_ptr<Data> data_;
    std::shared_ptr<QListWidget> collect_feeds_;
    std::shared_ptr<QListWidget> view_feeds_;
    std::vector<QString> l_old_collect_feed_;
    std::vector<QString> l_old_view_feed_;
    std::vector<QString> l_old_filters_;
    int options_type_;
    std::shared_ptr<QThreadPool> thread_pool_;
    QList<bool> l_items_for_remove_;
    std::shared_ptr<MainWindow> main_window_;
    std::shared_ptr<QLabel> download_feed_status_;

    std::shared_ptr<QLineEdit> cf_find_feed_;
    std::shared_ptr<QLabel> cf_label_search_;

    //QTextEdit *te_refresh_time;
    std::shared_ptr<QLabel> l_refresh_time_;
    std::shared_ptr<QCheckBox> cb_enable_notification_;
    std::shared_ptr<QSpinBox> sb_refresh_time_;

    std::shared_ptr<QLabel> l_proxy_url_;
    std::shared_ptr<QLabel> l_proxy_port_;
    std::shared_ptr<QTextEdit> te_proxy_url_;
    std::shared_ptr<QTextEdit> te_proxy_port_;
    std::shared_ptr<QCheckBox> cb_enable_proxy_;

    //filter options widgets
    std::shared_ptr<QPushButton> pb_add_filter_;
    std::shared_ptr<QTextEdit> te_add_filter_;
    std::shared_ptr<QListWidget> lw_filter_list_;
    std::shared_ptr<QLabel> l_filter_list_;
    std::shared_ptr<QPushButton> pb_remove_filter_;
    std::shared_ptr<QCheckBox> cb_enable_filtering_;


signals:
    void stateChanged (const QString &);
};
#endif // OPTIONSWINDOW_H

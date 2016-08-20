/*
    optionswindow.cpp
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
#include "optionswindow.h"
#include "ui_optionswindow.h"
#include <QDebug>

OptionsWindow::OptionsWindow(QWidget *parent, RSSThread *rss_thread, Data *data) :
    QWidget(parent),
    ui_(new Ui::OptionsWindow)
{
    ui_->setupUi(this);


    data_ = data;

    options_type_ = 1;

    view_window_ = view_window_;
    rss_thread_ = rss_thread;

    ui_->treeWidget->setHeaderLabel("Options");

    addItem("Collection feeds");
    addItem("Filters");
    addItem("Notifications");
    addItem("Proxy connection");

    download_feed_status_ = new QLabel(this);
    download_feed_status_->setGeometry(5,
                                      this->height() - (5+ ui_->OK_Button->height()),
                                      download_feed_status_->width(),
                                      download_feed_status_->height());

    //treewidget set geometry
    ui_->treeWidget->setGeometry(5,
                                5,
                                130,
                                this->height()- (15 + ui_->OK_Button->height()));
    ui_->Cancel_Button->setGeometry(this->width() - (5+ui_->Cancel_Button->width()),
                                   this->height() - (5+ ui_->Cancel_Button->height()),
                                   ui_->Cancel_Button->width(),
                                   ui_->Cancel_Button->height());
    ui_->OK_Button->setGeometry(ui_->Cancel_Button->x()-(5+ui_->OK_Button->width()),
                               ui_->Cancel_Button->y(),
                               ui_->OK_Button->width(),
                               ui_->OK_Button->height());

    //Collection feeds controls
    collect_feeds_ = new QListWidget(this);
    view_feeds_ = new QListWidget(this);
    collect_feeds_->setSelectionMode(QAbstractItemView::MultiSelection);
    view_feeds_->setSelectionMode(QAbstractItemView::MultiSelection);
    cf_find_feed_ = new QLineEdit(this);
    connect(cf_find_feed_,SIGNAL(textChanged(QString)), this, SLOT(on_textChanged(QString)));
    cf_label_search_ = new QLabel(this);

    cf_label_search_->setText("Search");
    ui_->pushButton->setText(">>");
    ui_->pushButton_2->setText("<<");
    ui_->pushButton_3->setText("Remove");

    int width = (this->width() - (25 + ui_->treeWidget->width() + ui_->pushButton->width()))/2;
    cf_label_search_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                                 5,
                                 50,
                                 cf_label_search_->height());

    cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+5,
                              5,
                              width - (cf_label_search_width() + 5),
                              cf_find_feed_->height());

    collect_feeds_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                               cf_find_feed_->height()+10,
                               width,
                               this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));

    ui_->pushButton_3->setGeometry(collect_feeds_->x(),
                                  collect_feeds_->y()  + collect_feeds_->height() + 5,
                                  ui_->pushButton_3->width(),
                                  ui_->pushButton_3->height());
    ui_->pushButton->setGeometry(collect_feeds_->x()+ collect_feeds_->width() +  5,
                                (ui_->pushButton_3->height()+10) + (collect_feeds_->height()/2 - (ui_->pushButton->height() + ui_->pushButton_2->height() + 10)/2),
                                ui_->pushButton->width(),
                                ui_->pushButton->height());
    ui_->pushButton_2->setGeometry(ui_->pushButton->x(),
                                  ui_->pushButton->y() + ui_->pushButton->height()+10,
                                  ui_->pushButton_2->width(),
                                  ui_->pushButton_2->height());
    view_feeds_->setGeometry(ui_->pushButton->x() + ui_->pushButton->width() + 5,
                            cf_find_feed_->height()+10,
                            width,
                            this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));

    collect_feeds_->show();
    view_feeds_->show();
    cf_find_feed_->show();
    cf_label_search_->show();

    thread_pool_ = new QThreadPool(this);
    thread_pool_->setMaxThreadCount(5);

    connect(collect_feeds_, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_collect_feeds_DoubleClicked(QListWidgetItem*)));

    //notification widgets
    sb_refresh_time_ = new QSpinBox (this);
    l_refresh_time_ = new QLabel(this);
    cb_enable_notification_ = new QCheckBox(this);

    l_refresh_time_->setGeometry(ui_->treeWidget->width() + 10,
                                 5,
                                 l_refresh_time_->width()+50,
                                 l_refresh_time_->height());
    l_refresh_time_->setText("Refresh feeds time (minutes):");
    l_refresh_time_->hide();

    sb_refresh_time_->setGeometry(ui_->treeWidget->width() + 10,
                                  l_refresh_time_->y()+l_refresh_time_->height() + 5,
                                  sb_refresh_time_->width(),
                                  sb_refresh_time_->height());
    sb_refresh_time_->setMinimum(1);
    sb_refresh_time_->setMaximum(60);
    sb_refresh_time_->hide();

    cb_enable_notification_->setGeometry(ui_->treeWidget->width() + 10,sb_refresh_time_->y() + sb_refresh_time_->height() + 5,
                                         cb_enable_notification_->width()+50,
                                         cb_enable_notification_->height());
    cb_enable_notification_->hide();
    cb_enable_notification_->setText("Enable notification window");
    cb_enable_notification_->setChecked(true);

    //proxy options
    l_proxy_url_ = new QLabel(this);
    l_proxy_port_ = new QLabel (this);
    te_proxy_url_ = new QTextEdit(this);
    te_proxy_port_ = new QTextEdit(this);
    cb_enable_proxy_ = new QCheckBox(this);

    cb_enable_proxy_->setChecked(false);
    cb_enable_proxy_->setText("Enable proxy connection");
    connect(cb_enable_proxy_, SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_proxy_clicked(bool)));
    l_proxy_url_->setText("Proxy address:");
    l_proxy_port_->setText("Proxy port:");

    cb_enable_proxy_->setGeometry(ui_->treeWidget->width() + 10,
                                  5,
                                  cb_enable_proxy_->width()+50,
                                  cb_enable_proxy_->height());
    l_proxy_url_->setGeometry(ui_->treeWidget->width() + 10,
                              cb_enable_proxy_->y() + cb_enable_proxy_->height()+5,
                              l_proxy_url_->width(),
                              l_proxy_url_->height());
    te_proxy_url_->setGeometry(ui_->treeWidget->width() + 10,
                               l_proxy_url_->y() +l_proxy_url_->height() + 5,
                               te_proxy_url_->width(),
                               te_proxy_url_->height());
    l_proxy_port_->setGeometry(ui_->treeWidget->width() + 10,
                               te_proxy_url_->y() + te_proxy_url_->height() + 5,
                               l_proxy_port_->width(),
                               l_proxy_port_->height());
    te_proxy_port_->setGeometry(ui_->treeWidget->width() + 10,
                                l_proxy_port_->y() + l_proxy_port_->height() + 5,
                                te_proxy_port_->width(),
                                te_proxy_port_->height());

    cb_enable_proxy_->hide();
    l_proxy_url_->hide();
    l_proxy_port_->hide();
    te_proxy_url_->hide();
    te_proxy_port_->hide();

    //filter options widgets
    pb_add_filter_ = new QPushButton(this);
    te_add_filter_ = new QTextEdit(this);
    lw_filter_list_ = new QListWidget(this);
    l_filter_list_ = new QLabel(this);
    pb_remove_filter_ = new QPushButton(this);
    cb_enable_filtering_ = new QCheckBox(this);

    cb_enable_filtering_->setGeometry(ui_->treeWidget->width() + 10,
                                      5,
                                      cb_enable_filtering_->width()+50,
                                      cb_enable_filtering_->height());
    pb_add_filter_->setGeometry(cb_enable_filtering_->x(),
                                cb_enable_filtering_->y()+cb_enable_filtering_->height() + 5,
                                pb_add_filter_->width(),
                                pb_add_filter_->height());
    te_add_filter_->setGeometry(pb_add_filter_->x() + pb_add_filter_->width() + 5,
                                pb_add_filter_->y(),
                                this->width() - (pb_add_filter_->x() + pb_add_filter_->width() + 10),
                                te_add_filter_->height());
    l_filter_list_->setGeometry(te_add_filter_->x(),
                                te_add_filter_->y() + te_add_filter_->height() + 5,
                                l_filter_list_->width(),
                                l_filter_list_->height());
    lw_filter_list_->setGeometry(te_add_filter_->x(),
                                 l_filter_list_->y()+l_filter_list_->height()+5,
                                 this->width() - (l_filter_list_->x()+5),
                                 this->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ui_->OK_Button->height()));
    pb_remove_filter_->setGeometry(ui_->treeWidget->width()+10,
                                  lw_filter_list_->y(),
                                  pb_remove_filter_->width(),
                                  pb_remove_filter_->height());

    cb_enable_filtering_->setChecked(false);
    cb_enable_filtering_->setText("Enable filtering");
    pb_add_filter_->setText("Add");
    pb_remove_filter_->setText("Remove");
    l_filter_list_->setText("Filter List:");

    connect(cb_enable_filtering_, SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_filtering_clicked(bool)));
    connect(pb_add_filter_, SIGNAL(clicked()), this, SLOT(on_pb_add_filter_clicked()));
    connect(pb_remove_filter_, SIGNAL(clicked()), this, SLOT(on_pb_remove_filter()));

    cb_enable_filtering_->hide();
    pb_add_filter_->hide();
    te_add_filter_->hide();
    lw_filter_list_->hide();
    l_filter_list_->hide();
    pb_remove_filter_->hide();
}

OptionsWindow::~OptionsWindow()
{
    delete ui_;
    delete collect_feeds_;
    delete view_feeds_;
    l_old_collect_feed_.clear();
    l_old_view_feed_.clear();
    l_old_filters_.clear();
    delete sb_refresh_time_;
    delete cb_enable_notification_;
    delete  l_proxy_url_;
    delete l_proxy_port_;
    delete te_proxy_url_;
    delete te_proxy_port_;
    delete cb_enable_proxy_;
    delete cb_enable_filtering_;
    delete pb_add_filter_;
    delete te_add_filter_;
    delete lw_filter_list_;
    delete l_filter_list_;
    delete pb_remove_filter_;
    delete cf_find_feed_;
    delete cf_label_search_;
}

void OptionsWindow::onFinish(QString name, bool finish)
{
    if (finish)
    {
        view_window_->onUpdate(l_items_for_remove_);
        this->close();
        return;
    }
    name = "Downloading: " + name;
    returnModifedString(name);
    download_feed_status_->setText(name);

}

//modify label string to fit in size of window
void OptionsWindow::returnModifedString(QString &str)
{
    QRect rect;
    QFontMetrics fm(download_feed_status_->font());
    QString str_tmp = str, add_str="";
    int pixel_width = 0, dots_width=0, window_width = 0;
    window_width = ui_->Cancel_Button->x() - 10;

    rect = fm.boundingRect("...");
    dots_width = rect.width();
    rect = fm.boundingRect(str_tmp);
    pixel_width=rect.width();
    if (pixel_width>=window_width)
        add_str+="...";

    while (pixel_width >= window_width)
    {
        str_tmp = str_tmp.left(str_tmp.size()-1);
        rect = fm.boundingRect(str_tmp);
        pixel_width=rect.width() + dots_width;
    }
    str = str_tmp + add_str;
}

//add item to tree widget
void OptionsWindow::addItem(QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    ui_->treeWidget->addTopLevelItem(item);
}

//add string to collect_feeds (QListWidget var)
int OptionsWindow::addStringToWatchList(QString cur_text)
{
    int count = collect_feeds_->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical string
    for(int row = 0; row < collect_feeds_->count(); row++)
    {
        QListWidgetItem *item = collect_feeds_->item(row);
        if (cur_text == item->text())
            return 1;
    }

    collect_feeds_->insertItem(count, cur_text); //insert new element to the end of list widget

    return 0;
}

//fill view_feeds (QListWidget var)
void OptionsWindow::fillViewListView()
{
    boost::ptr_vector<QString> tmp;
    data_base_.getFavoriteFeeds(&tmp);

    l_old_view_feed_.clear();

    boost::ptr_vector<QString>::iterator it;
    for (it=tmp.begin(); it!=tmp.end(); ++it)
    {
        view_feeds_->insertItem(view_feeds_->count(), *it);
        l_old_view_feed_.push_back(new QString(*it));
    }
}

//add string to view_feeds (QListWidget var)
int OptionsWindow::addStringToViewList(QString cur_text)
{
    int count = view_feeds_->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical strings
    for(int row = 0; row < view_feeds_->count(); row++)
    {
        QListWidgetItem *item = view_feeds_->item(row);
        if (cur_text == item->text())
            return 1;
    }
    view_feeds_->insertItem(count, cur_text); //insert new element in the end of list widget

    return 0;
}

//update 'rss' DB table and 'site_struct->s_struct' vector list
void OptionsWindow::rssTableUpdate()
{
    bool isAddedToView = false;
    rss_thread_->is_add_option_ = false;

    l_items_for_remove_.clear();

    if (l_old_view_feed_.size()==0)
    {
        //add all data from view_feeds (QListWidget var)
        for (int i=0;  i<view_feeds_->count(); i++)
        {
            QString url, version;
            findAndReturnURLAndVersion(view_feeds_->item(i)->text(),url,version);
            if (url == "")
                continue;

            insertRowToRSSTable(view_feeds_->item(i)->text(), url, version);
            isAddedToView = true;
            data_->pushBack(rss_thread_->initStruct(view_feeds_->item(i)->text(),"RSS",url));
            data_->at(data_->size()-1)->setIsRead(false);
            data_->at(data_->size()-1)->setVersion(version);
            thread_pool_->start(rss_thread_);
        }
        if (!isAddedToView)
            this->close();
        return;
    }

    //remove all data from 'rss' table
    if (view_feeds_->count() == 0)
    {
        while (data_->size()>0)
            data_->erase(0);
        removeDataFromRSSTable("", 1);
    }

    //init l_items_for_remove
    for(uint i=0; i<l_old_view_feed_.size(); i++)
        l_items_for_remove_.push_back(0);

    for (uint i=0;  i<view_feeds_->count(); i++)
    {
        //qDebug()<<view_feeds->item(i)->text();
        for (uint j = 0; j<l_old_view_feed_.size(); j++)
        {
            //qDebug()<<"COMPARING WITH: "<< l_old_view_feed[j];
            if (view_feeds_->item(i)->text() == l_old_view_feed_[j])
            {
                l_items_for_remove_[j] = 1;
                break;
            }
            if (l_old_view_feed_.size()-1 == j)
            {

                //find url and version of site_name
                QString url, version;
                findAndReturnURLAndVersion(view_feeds_->item(i)->text(),url,version);
                insertRowToRSSTable(view_feeds_->item(i)->text(), url, version);
                data_->pushBack(rss_thread_->initStruct(view_feeds_->item(i)->text(),"RSS",url));
                data_->at(data_->size()-1)->setIsRead(false);
                data_->at(data_->size()-1)->setVersion(version);
                isAddedToView = true;
                thread_pool_->start(rss_thread_);
            }
        }
    }

    QList<bool> l_item_indexes_from_site_struct;
    //init l_item_indexes_from_site_struct;
    for (uint i=0; i<data_->size(); i++)
        l_item_indexes_from_site_struct.push_back(1);

    //remove old items
    for (int i=0; i<l_items_for_remove_.size(); i++)
        if (l_items_for_remove_[i] == 0)
        {
            removeDataFromRSSTable(l_old_view_feed_[i],0);
            for (uint j=0; j<data_->size(); j++)
            {
                //qDebug()<<"COMPARING "<<l_old_view_feed[i]<<" WITH: "<<site_struct->s_struct[j].site_name;
                if (l_old_view_feed_[i] == data_->at(j)->getSiteName())
                {
                    l_item_indexes_from_site_struct[j] = 0;
                    break;
                }
            }
        }

    l_items_for_remove_.swap(l_item_indexes_from_site_struct);
    if (!isAddedToView)
    {
        rss_thread_->is_add_option_ = true;
        this->close();
        view_window_->onUpdate(l_items_for_remove_);
    }
}

//remove site_name data from 'rss' table in 'sites.db3'. If all_data == 1,
//then remove all data from 'rss' table
void OptionsWindow::removeDataFromRSSTable(QString site_name, bool all_data)
{
    data_base_.removeDataFromRSSTable(site_name, all_data);
}

//insert row to 'rss' DB table
void OptionsWindow::insertRowToRSSTable(QString name, QString url, QString version)
{
    data_base_.insertIntoFavoriteFeeds(name, url, version);
}

//from site_name, return url and version
void OptionsWindow::findAndReturnURLAndVersion(QString site_name, QString &url, QString &version)
{
    data_base_.findAndReturnURLAndVersion(site_name, url, version);
}

void OptionsWindow::updateFiltersTable()
{
     view_window_->filters_qlist.clear();
     data_base_.removeDataFromFilters(); //delete all old filters data

     for (int i=0;  i<lw_filter_list_->count(); i++)
     {
         insertRowToFiltersTable(lw_filter_list_->item(i)->text());
         view_window_->filters_qlist.append(lw_filter_list_->item(i)->text());
     }
     view_window_->initTextBrowser();
}


void OptionsWindow::loadOptions()
{
    QFile file("../resources/Options");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Error!", "Can't read \'Options\' file: " + file.errorString());
        return;
    }

    QTextStream in(&file);

    QString what ="";
    QString line = in.readLine();

    //get refresh time
    if (line.length()<14)
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }
    if (line[13] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }

    int i=14;
    while (line[i] != '\n' && i<line.length())
    {
        what+=line[i];
        i++;
    }
    i = what.toInt();
    sb_refresh_time_->setValue(i);

    line = in.readLine();

    if (line.length()<21)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[20] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }

    if (line[21]=='0')
        cb_enable_notification_->setChecked(false);
    else if (line[21] == '1')
        cb_enable_notification_->setChecked(true);
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from a \'Options\' file!");


    // enable/disable proxy connection option
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[14] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for enable proxy connection from \'Options\' file!");
        file.close();
        return;
    }

    if (line[15]=='0')
    {
        cb_enable_proxy_->setChecked(false);
        l_proxy_url_->setEnabled(false);
        l_proxy_port_->setEnabled(false);
        te_proxy_url_->setEnabled(false);
        te_proxy_port_->setEnabled(false);
    }
    else if (line[15] == '1')
    {
        cb_enable_proxy_->setChecked(true);
        l_proxy_url_->setEnabled(true);
        l_proxy_port_->setEnabled(true);
        te_proxy_url_->setEnabled(true);
        te_proxy_port_->setEnabled(true);
    }
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from \'Options\' file!");

    //load proxy server address
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        file.close();
        return;
    }

    if (line[14]!=' ')
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        file.close();
        return;
    }

    i=15;
    QString str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    te_proxy_url_->setText(str_tmp);

    //laod proxy port information
    line = in.readLine();
    if (line.length()<12)
    {
        QMessageBox::critical(0, "Error!", "Can't laod proxy port from \'Options\' file!");
        file.close();
        return;
    }
    if (line[11]!=' ')
    {

        QMessageBox::critical(0, "Error!", "Can't load proxy port from \'Options\' file!");
        file.close();
        return;
    }

    i=12;
    str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    te_proxy_port_->setText(str_tmp);



    // enable/disable proxy connection option
    line = in.readLine();

    if (line.length()<17)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for filters from \'Options\' file!");
        file.close();
        return;
    }
    if (line[16] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for filters from \'Options\' file!");
        file.close();
        return;
    }

    if (line[17]=='0')
    {
        cb_enable_filtering_->setChecked(false);
        pb_add_filter_->setEnabled(false);
        te_add_filter_->setEnabled(false);
        lw_filter_list_->setEnabled(false);
        l_filter_list_->setEnabled(false);
        pb_remove_filter_->setEnabled(false);
    }
    else if (line[17] == '1')
    {
        cb_enable_filtering_->setChecked(true);
        pb_add_filter_->setEnabled(true);
        te_add_filter_->setEnabled(true);
        lw_filter_list_->setEnabled(true);
        l_filter_list_->setEnabled(true);
        pb_remove_filter_->setEnabled(true);
    }
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Filter window\' from \'Options\' file!");

    file.close();
}

//save options in 'Options' file
void OptionsWindow::saveOptions()
{
    QFile file("../resouce/Options");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    //notifications
    out << "Refresh time: " << QString::number(sb_refresh_time_->value()) <<'\n';
    rss_thread_->setRefreshTime(sb_refresh_time_->value());
    if (cb_enable_notification_->isChecked())
    {
        out << "Notification window: 1\n";
        rss_thread_->setEnableNotificationWindow(1);
    }
    else
    {
        out << "Notification window: 0\n";
        rss_thread_->setEnableNotificationWindow(0);
    }

    //proxy
    if (cb_enable_proxy_->isChecked())
    {
        out << "Enabled Proxy: 1\n";
        rss_thread_->enabled_proxy_connection_ = 1;
    }
    else
    {
        out << "Enabled Proxy: 0\n";
        rss_thread_->enabled_proxy_connection_ = 0;
    }

    out<<"Proxy Address: "<< te_proxy_url_->toPlainText()<<"\n";
    rss_thread_->proxy_url_ = te_proxy_url_->toPlainText();
    out<<"Proxy Port: "<< te_proxy_port_->toPlainText()<<"\n";
    rss_thread_->proxy_port_ = te_proxy_port_->toPlainText();


    //filters
    if (cb_enable_filtering_->isChecked())
    {
        out << "Enabled Filters: 1\n";
        rss_thread_->enabled_filters_ = 1;
    }
    else
    {
        out << "Enabled Filters: 0\n";
        rss_thread_->enabled_filters_ = 0;
    }

    file.close();
}

//update collect_feeds (QListWidget var)
void OptionsWindow::updateCollectFeedListView()
{
    if (collect_feeds_->count() == 0)
    {
        for (uint i=0; i<l_old_collect_feed_.size(); i++)
            removeDataFromCollectFeeds(l_old_collect_feed_[i]);
        return;
    }

    for (uint i=0; i<l_old_collect_feed_.size(); i++)
    {
        for (int j=0; j<collect_feeds_->count(); j++)
        {
            if (l_old_collect_feed_[i] == collect_feeds_->item(j)->text())
                break;
            if (j==collect_feeds_->count()-1)
                removeDataFromCollectFeeds(l_old_collect_feed_[i]);
        }
    }
}

//fill collect_feed (QListWidget)
void OptionsWindow::fillCollectListView()
{
    boost::ptr_vector<QString>tmp;
    data_base_.getCollectFeeds(&tmp);

    l_old_collect_feed_.clear();

    boost::ptr_vector<QString>::iterator it;

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        collect_feeds_->insertItem(collect_feeds_->count(), *it);
        l_old_collect_feed_.push_back(new QString(*it));
    }
}

void OptionsWindow::fillFilterListView()
{
    boost::ptr_vector <QString> tmp;
    data_base_.getFilterList(&tmp);

    l_old_filters_.clear();

    boost::ptr_vector <QString>::iterator it;

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        addStringToFilterList(*it);
        l_old_filters_.push_back(new QString(*it));
    }
}

//resize window event
void OptionsWindow::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);

    ui_->treeWidget->setGeometry(5,5, 130, this->height()- (15 + ui_->OK_Button->height()));

    ui_->Cancel_Button->setGeometry(this->width() - 5+ui_->Cancel_Button->width(),
            this->height() - (5+ ui_->Cancel_Button->height()),
            ui_->Cancel_Button->width(), ui_->Cancel_Button->height());

    ui_->OK_Button->setGeometry(ui_->Cancel_Button->x()-(5+ui_->OK_Button->width()),
                                ui_->Cancel_Button->y(),
                                ui_->OK_Button->width(),
                                ui_->OK_Button->height());

    download_feed_status_->setGeometry(5,
                                      this->height() - (5+ ui_->OK_Button->height()),
                                      download_feed_status_->width(),
                                      download_feed_status_->height());

    if (options_type_ == 1)
    {
        int width = (this->width() - (25 + ui_->treeWidget->width() + ui_->pushButton->width()))/2;
        collect_feeds_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                                   cf_find_feed_->height()+10,
                                   width, this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));
        ui_->pushButton_3->setGeometry(collect_feeds_->x(),
                                       collect_feeds_->y() + collect_feeds_->height() + 5,
                                       ui_->pushButton_3->width(),
                                       ui_->pushButton_3->height());
        cf_label_search_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                                     5,
                                     50,
                                     cf_label_search_->height());
        cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+5,
                                  5,
                                  width - (cf_label_search_width() + 5) ,
                                  cf_find_feed_->height());
        ui_->pushButton->setGeometry(collect_feeds_->x()+ collect_feeds_->width() +  5,
                                    (ui_->pushButton_3->height()+10) + (collect_feeds_->height()/2 - ( ui_->pushButton->height() + ui_->pushButton_2->height() + 10)/2),
                                    ui_->pushButton->width(),
                                    ui_->pushButton->height());
        ui_->pushButton_2->setGeometry(ui_->pushButton->x(),
                                      ui_->pushButton->y() + ui_->pushButton->height()+10,
                                      ui_->pushButton_2->width(),
                                      ui_->pushButton_2->height());
        view_feeds_->setGeometry(ui_->pushButton->x() + ui_->pushButton->width() + 5,cf_find_feed_->height()+10 ,
                                width,
                                this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));
    }
    else if (options_type_ == 2)
    {

        te_add_filter_->setGeometry(pb_add_filter_->x() + pb_add_filter_->width() + 5,
                                   5,
                                   this->width() - (pb_add_filter_->x() + pb_add_filter_->width() + 10),
                                   te_add_filter_->height());
        lw_filter_list_->setGeometry(te_add_filter_->x(),
                                    l_filter_list_->y()+l_filter_list_->height()+5,
                                    this->width() - (l_filter_list_->x()+5),
                                    this->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ui_->OK_Button->height()));
    }
}

//show event
void OptionsWindow::showEvent(QShowEvent *event)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadOptions();

    download_feed_status_->hide();
    collect_feeds_->clear();
    view_feeds_->clear();
    lw_filter_list_->clear();
    fillCollectListView();
    fillViewListView();
    fillFilterListView();
    this->setEnabled(true);
}

//'>>' button has been clicked
void OptionsWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> l;
    l = collect_feeds_->selectedItems();
    if (l.size()==0)
        return;

    for(int i=0; i<l.size(); i++)
        addStringToViewList(l[i]->text());
}

//'<<' button has been clicked
void OptionsWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem*> l;
    l = view_feeds_->selectedItems();
    if (l.size()==0)
        return;

    for (int i=l.size()-1; i>=0; i--)
        delete l[i];
}

//'OK' button event
void OptionsWindow::on_OK_Button_clicked()
{
    download_feed_status_->show();
    this->setEnabled(false);
    saveOptions();
    rss_thread_->setProxySettings();
    updateFiltersTable();
    updateCollectFeedListView();
    rssTableUpdate();
}

//'Cancel' button has been clicked
void OptionsWindow::on_Cancel_Button_clicked()
{
    this->close();
}

//'Removed' button has been clicked
void OptionsWindow::on_pushButton_3_clicked()
{
    if (collect_feeds_->currentItem()==NULL)
        return;

    //remove from list widget
    QList<QListWidgetItem*> l;
    l = collect_feeds_->selectedItems();
    if (l.size()==0)
        return;

    //remove item(s) from collect_feeds
    for (int i=l.size()-1; i>=0; i--)
    {
        for (int j = 0; j<view_feeds_->count(); j++)
        {
            QListWidgetItem *item = view_feeds_->item(j);
            if (l[i]->text() == item->text())
            {
                delete item;
                break;
            }
        }

        delete l[i];
    }
}

void OptionsWindow::on_collect_feeds_DoubleClicked(QListWidgetItem *item)
{
    addStringToViewList(item->text());
}

//treeWidget has been clicked
void OptionsWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    QString t = index.data().toByteArray().data();

    if (t == "Collection feeds")
    {
        showCollectionFeeds();
        hideNotifications();
        hideProxyConnection();
        hideFilters();
    }
    else if (t == "Filters")
    {
        showFilters();
        hideCollectionFeeds();
        hideNotifications();
        hideProxyConnection();
    }
    else if (t == "Notifications")
    {
        showNotifications();
        hideCollectionFeeds();
        hideProxyConnection();
        hideFilters();
    }
    else if (t == "Proxy connection")
    {
        showProxyConnection();
        hideCollectionFeeds();
        hideNotifications();
        hideFilters();
    }
}

void OptionsWindow::on_cb_enable_proxy_clicked(bool state)
{
    if (state)
    {
        l_proxy_url_->setEnabled(true);
        l_proxy_port_->setEnabled(true);
        te_proxy_url_->setEnabled(true);
        te_proxy_port_->setEnabled(true);
    }
    else
    {
        l_proxy_url_->setEnabled(false);
        l_proxy_port_->setEnabled(false);
        te_proxy_url_->setEnabled(false);
        te_proxy_port_->setEnabled(false);
    }
}

void OptionsWindow::on_cb_enable_filtering_clicked(bool state)
{
    if (state)
    {
        pb_add_filter_->setEnabled(true);
        te_add_filter_->setEnabled(true);
        lw_filter_list_->setEnabled(true);
        l_filter_list_->setEnabled(true);
        pb_remove_filter_->setEnabled(true);
    }
    else
    {
        pb_add_filter_->setEnabled(false);
        te_add_filter_->setEnabled(false);
        lw_filter_list_->setEnabled(false);
        l_filter_list_->setEnabled(false);
        pb_remove_filter_->setEnabled(false);
    }
}

void OptionsWindow::on_pb_add_filter_clicked()
{
    if (addStringToFilterList(te_add_filter_->toPlainText()))
    {
        te_add_filter_->setText("");
        return;
    }
    te_add_filter_->setText("");
}

//remove selected item in filter option
void OptionsWindow::on_pb_remove_filter()
{
    if (lw_filter_list_->currentItem()==NULL)
        return;

    QList<QListWidgetItem*> l;
    l = lw_filter_list_->selectedItems();
    if (l.size()==0)
        return;

    delete l[0];
}

void OptionsWindow::insertRowToFiltersTable(QString filter_name)
{
    data_base_.insertRowToFiltersTable(filter_name);
}

void OptionsWindow::removeDataFromCollectFeeds(QString site_name)
{
    data_base_.removeDataFromCollectFeeds(site_name);
}

//Filter option: adding string to filter list
int OptionsWindow::addStringToFilterList(QString cur_text)
{
    int count = lw_filter_list_->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical string
    for(int row = 0; row < lw_filter_list_->count(); row++)
    {
        QListWidgetItem *item = lw_filter_list_->item(row);
        // process item
        if (cur_text == item->text())
            return 1;
    }

    lw_filter_list_->insertItem(count, cur_text); //insert new element in the end of list widget
    return 0;
}

void OptionsWindow::on_textChanged(QString text) //cf_find_feeds text changed event
{
    boost::ptr_vector<QString> tmp;
    data_base_.getCollectFeedsThatContainingText(text, &tmp);

    collect_feeds_->clear();

    boost::ptr_vector<QString>::iterator it;
    for (it = tmp.begin(); it!=tmp.end(); ++it)
        addStringToWatchList(*it);
}

int OptionsWindow::cf_label_search_width()
{
    QFontMetrics fm(cf_label_search_->font());
    QRect rect = fm.boundingRect(cf_label_search_->text());

    return rect.width();
}

//show widgets
void OptionsWindow::showCollectionFeeds()
{
    options_type_ = 1;
    int width = (this->width() - (25 + ui_->treeWidget->width() + ui_->pushButton->width()))/2;
    collect_feeds_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                               cf_find_feed_->height()+10,
                               width,
                               this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));
    ui_->pushButton_3->setGeometry(collect_feeds_->x(),
                                  collect_feeds_->y() + collect_feeds_->height() + 5,
                                  ui_->pushButton_3->width(),
                                  ui_->pushButton_3->height());
    cf_label_search_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                                 5,
                                 50,
                                 cf_label_search_->height());
    cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+5,
                              5,
                              width - (cf_label_search_width() + 5) ,
                              cf_find_feed_->height());
    ui_->pushButton->setGeometry(collect_feeds_->x()+ collect_feeds_->width() +  5,
                                (ui_->pushButton_3->height()+10) + (collect_feeds_->height()/2 - ( ui_->pushButton->height() + ui_->pushButton_2->height() + 10)/2),
                                ui_->pushButton->width(),
                                ui_->pushButton->height());
    ui_->pushButton_2->setGeometry(ui_->pushButton->x(),
                                  ui_->pushButton->y() + ui_->pushButton->height()+10,
                                  ui_->pushButton_2->width(),
                                  ui_->pushButton_2->height());
    view_feeds_->setGeometry(ui_->pushButton->x() + ui_->pushButton->width() + 5,
                            cf_find_feed_->height()+10 ,
                            width,
                            this->height()-(20 +cf_find_feed_->height() + ui_->OK_Button->height()));

    collect_feeds_->show();
    ui_->pushButton->show();
    ui_->pushButton_2->show();
    ui_->pushButton_3->show();
    view_feeds_->show();
    cf_find_feed_->show();
    cf_label_search_->show();

}

void OptionsWindow::showFilters()
{
    cb_enable_filtering_->show();
    pb_add_filter_->show();
    te_add_filter_->show();
    lw_filter_list_->show();
    l_filter_list_->show();
    pb_remove_filter_->show();

    options_type_ = 2;
}

void OptionsWindow::showNotifications()
{
    options_type_ = 3;

    sb_refresh_time_->show();
    l_refresh_time_->show();
    cb_enable_notification_->show();
}

void OptionsWindow::showProxyConnection()
{
    options_type_ = 4;

    cb_enable_proxy_->show();
    l_proxy_url_->show();
    l_proxy_port_->show();
    te_proxy_url_->show();
    te_proxy_port_->show();
}

//hide widgets
void OptionsWindow::hideCollectionFeeds()
{
    collect_feeds_->hide();
    ui_->pushButton->hide();
    ui_->pushButton_2->hide();
    ui_->pushButton_3->hide();
    view_feeds_->hide();
    cf_find_feed_->hide();
    cf_label_search_->hide();
}

void OptionsWindow::hideFilters()
{
    cb_enable_filtering_->hide();
    pb_add_filter_->hide();
    te_add_filter_->hide();
    lw_filter_list_->hide();
    l_filter_list_->hide();
    pb_remove_filter_->hide();
}

void OptionsWindow::hideNotifications()
{
    sb_refresh_time_->hide();
    l_refresh_time_->hide();
    cb_enable_notification_->hide();
}
void OptionsWindow::hideProxyConnection()
{

    cb_enable_proxy_->hide();
    l_proxy_url_->hide();
    l_proxy_port_->hide();
    te_proxy_url_->hide();
    te_proxy_port_->hide();
}


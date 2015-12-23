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

OptionsWindow::OptionsWindow(QWidget *parent, RSSThread *ss, ViewWindow *view_window, Data *data_tmp) :
    QWidget(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);


    data = data_tmp;

    options_type = 1;

    vw = view_window;
    site_struct = ss;

    ui->treeWidget->setHeaderLabel("Options");

    addItem("Collection feeds");
    addItem("Filters");
    addItem("Notifications");
    addItem("Proxy connection");

    download_feed_status = new QLabel(this);
    download_feed_status->setGeometry(5,this->height() - (5+ ui->OK_Button->height()),download_feed_status->width(), download_feed_status->height());

    //treewidget set geometry
    ui->treeWidget->setGeometry(5,5, 130, this->height()- (15 + ui->OK_Button->height()));
    ui->Cancel_Button->setGeometry(this->width() - (5+ui->Cancel_Button->width()),this->height() - (5+ ui->Cancel_Button->height()), ui->Cancel_Button->width(), ui->Cancel_Button->height());
    ui->OK_Button->setGeometry(ui->Cancel_Button->x()-(5+ui->OK_Button->width()),ui->Cancel_Button->y(), ui->OK_Button->width(), ui->OK_Button->height());

    //Collection feeds controls
    collect_feeds = new QListWidget(this);
    view_feeds = new QListWidget(this);
    collect_feeds->setSelectionMode(QAbstractItemView::MultiSelection);
    view_feeds->setSelectionMode(QAbstractItemView::MultiSelection);
    cf_find_feed = new QLineEdit(this);
    connect(cf_find_feed,SIGNAL(textChanged(QString)), this, SLOT(on_textChanged(QString)));
    cf_label_search = new QLabel(this);

    cf_label_search->setText("Search");
    ui->pushButton->setText(">>");
    ui->pushButton_2->setText("<<");
    ui->pushButton_3->setText("Remove");

    int width = (this->width() - (25 + ui->treeWidget->width() + ui->pushButton->width()))/2;
    cf_label_search->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, 5, 50, cf_label_search->height());
    cf_find_feed->setGeometry(cf_label_search->x() + cf_label_search_width()+5, 5,width - (cf_label_search_width() + 5) , cf_find_feed->height());

    collect_feeds->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, cf_find_feed->height()+10, width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));

    ui->pushButton_3->setGeometry(collect_feeds->x(),collect_feeds->y()  + collect_feeds->height() + 5,  ui->pushButton_3->width(), ui->pushButton_3->height());
    ui->pushButton->setGeometry(collect_feeds->x()+ collect_feeds->width() +  5, (ui->pushButton_3->height()+10) + (collect_feeds->height()/2 - ( ui->pushButton->height() + ui->pushButton_2->height() + 10)/2),ui->pushButton->width(), ui->pushButton->height());
    ui->pushButton_2->setGeometry(ui->pushButton->x(), ui->pushButton->y() + ui->pushButton->height()+10, ui->pushButton_2->width(), ui->pushButton_2->height());
    view_feeds->setGeometry(ui->pushButton->x() + ui->pushButton->width() + 5,cf_find_feed->height()+10 ,width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));

    collect_feeds->show();
    view_feeds->show();
    cf_find_feed->show();
    cf_label_search->show();

    tp = new QThreadPool(this);
    tp->setMaxThreadCount(5);

    connect(collect_feeds, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_collect_feeds_DoubleClicked(QListWidgetItem*)));

    //notification widgets
    sb_refresh_time = new QSpinBox (this);
    l_refresh_time = new QLabel(this);
    cb_enable_notification = new QCheckBox(this);

    l_refresh_time->setGeometry(ui->treeWidget->width() + 10, 5, l_refresh_time->width()+50, l_refresh_time->height());
    l_refresh_time->setText("Refresh feeds time (minutes):");
    l_refresh_time->hide();

    sb_refresh_time->setGeometry(ui->treeWidget->width() + 10, l_refresh_time->y()+l_refresh_time->height() + 5, sb_refresh_time->width(), sb_refresh_time->height());
    sb_refresh_time->setMinimum(1);
    sb_refresh_time->setMaximum(60);
    sb_refresh_time->hide();

    cb_enable_notification->setGeometry(ui->treeWidget->width() + 10,sb_refresh_time->y() + sb_refresh_time->height() + 5, cb_enable_notification->width()+50, cb_enable_notification->height());
    cb_enable_notification->hide();
    cb_enable_notification->setText("Enable notification window");
    cb_enable_notification->setChecked(true);

    //proxy options
    l_proxy_url = new QLabel(this);
    l_proxy_port = new QLabel (this);
    te_proxy_url = new QTextEdit(this);
    te_proxy_port = new QTextEdit(this);
    cb_enable_proxy = new QCheckBox(this);

    cb_enable_proxy->setChecked(false);
    cb_enable_proxy->setText("Enable proxy connection");
    connect(cb_enable_proxy, SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_proxy_clicked(bool)));
    l_proxy_url->setText("Proxy address:");
    l_proxy_port->setText("Proxy port:");

    cb_enable_proxy->setGeometry(ui->treeWidget->width() + 10,5,cb_enable_proxy->width()+50, cb_enable_proxy->height());
    l_proxy_url->setGeometry(ui->treeWidget->width() + 10, cb_enable_proxy->y() + cb_enable_proxy->height()+5, l_proxy_url->width(), l_proxy_url->height());
    te_proxy_url->setGeometry(ui->treeWidget->width() + 10, l_proxy_url->y() +l_proxy_url->height() + 5 ,te_proxy_url->width(), te_proxy_url->height());
    l_proxy_port->setGeometry(ui->treeWidget->width() + 10, te_proxy_url->y() + te_proxy_url->height() + 5,l_proxy_port->width(), l_proxy_port->height());
    te_proxy_port->setGeometry(ui->treeWidget->width() + 10, l_proxy_port->y() + l_proxy_port->height() + 5,te_proxy_port->width(), te_proxy_port->height());

    cb_enable_proxy->hide();
    l_proxy_url->hide();
    l_proxy_port->hide();
    te_proxy_url->hide();
    te_proxy_port->hide();

    //filter options widgets
    pb_add_filter = new QPushButton(this);
    te_add_filter = new QTextEdit(this);
    lw_filter_list = new QListWidget(this);
    l_filter_list = new QLabel(this);
    pb_remove_filter = new QPushButton(this);

    pb_add_filter->setGeometry(ui->treeWidget->width()+10,5,pb_add_filter->width(), pb_add_filter->height());
    te_add_filter->setGeometry(pb_add_filter->x() + pb_add_filter->width() + 5,5,this->width() - (pb_add_filter->x() + pb_add_filter->width() + 10), te_add_filter->height());
    l_filter_list->setGeometry(te_add_filter->x(), te_add_filter->y() + te_add_filter->height() + 5, l_filter_list->width(), l_filter_list->height());
    lw_filter_list->setGeometry(te_add_filter->x(), l_filter_list->y()+l_filter_list->height()+5, this->width() - (l_filter_list->x()+5), this->height() - (l_filter_list->y()+ l_filter_list->height()+15+ ui->OK_Button->height()));
    pb_remove_filter->setGeometry(ui->treeWidget->width()+10, lw_filter_list->y(), pb_remove_filter->width(), pb_remove_filter->height());

    pb_add_filter->setText("Add");
    pb_remove_filter->setText("Remove");
    l_filter_list->setText("Filter List:");

    connect(pb_add_filter, SIGNAL(clicked()), this, SLOT(on_pb_add_filter_clicked()));
    connect(pb_remove_filter, SIGNAL(clicked()), this, SLOT(on_pb_remove_filter()));

    pb_add_filter->hide();
    te_add_filter->hide();
    lw_filter_list->hide();
    l_filter_list->hide();
    pb_remove_filter->hide();
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
    delete collect_feeds;
    delete view_feeds;
    l_old_collect_feed.clear();
    l_old_view_feed.clear();
    l_old_filters.clear();
    delete sb_refresh_time;
    delete cb_enable_notification;
    delete  l_proxy_url;
    delete l_proxy_port;
    delete te_proxy_url;
    delete te_proxy_port;
    delete cb_enable_proxy;
    delete pb_add_filter;
    delete te_add_filter;
    delete lw_filter_list;
    delete l_filter_list;
    delete pb_remove_filter;
    delete cf_find_feed;
    delete cf_label_search;
}

void OptionsWindow::onFinish(QString name, bool finish)
{
    if (finish)
    {
        vw->onUpdate(l_items_for_remove);
        this->close();
        return;
    }
    name = "Downloading: " + name;
    returnModifedString(name);
    download_feed_status->setText(name);

}

//modify label string to fit in size of window
void OptionsWindow::returnModifedString(QString &str)
{
    QRect rect;
    QFontMetrics fm(download_feed_status->font());
    QString str_tmp = str, add_str="";
    int pixel_width = 0, dots_width=0, window_width = 0;
    window_width = ui->Cancel_Button->x() - 10;

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
    ui->treeWidget->addTopLevelItem(item);
}

//add string to collect_feeds (QListWidget var)
int OptionsWindow::addStringToWatchList(QString cur_text)
{
    int count = collect_feeds->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical string
    for(int row = 0; row < collect_feeds->count(); row++)
    {
        QListWidgetItem *item = collect_feeds->item(row);
        if (cur_text == item->text())
            return 1;
    }

    collect_feeds->insertItem(count, cur_text); //insert new element to the end of list widget

    return 0;
}

//fill view_feeds (QListWidget var)
void OptionsWindow::fillViewListView()
{
    boost::ptr_vector<QString> tmp;
    db.getFavoriteFeeds(&tmp);

    l_old_view_feed.clear();

    boost::ptr_vector<QString>::iterator it;
    for (it=tmp.begin(); it!=tmp.end(); ++it)
    {
        view_feeds->insertItem(view_feeds->count(), *it);
        l_old_view_feed.push_back(new QString(*it));
    }
}

//add string to view_feeds (QListWidget var)
int OptionsWindow::addStringToViewList(QString cur_text)
{
    int count = view_feeds->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical strings
    for(int row = 0; row < view_feeds->count(); row++)
    {
        QListWidgetItem *item = view_feeds->item(row);
        if (cur_text == item->text())
            return 1;
    }
    view_feeds->insertItem(count, cur_text); //insert new element in the end of list widget

    return 0;
}

//update 'rss' DB table and 'site_struct->s_struct' vector list
void OptionsWindow::rssTableUpdate()
{
    bool isAddedToView = false;
    site_struct->isAddOption = false;

    l_items_for_remove.clear();

    if (l_old_view_feed.size()==0)
    {
        //add all data from view_feeds (QListWidget var)
        for (int i=0;  i<view_feeds->count(); i++)
        {
            QString url, version;
            findAndReturnURLAndVersion(view_feeds->item(i)->text(),url,version);
            if (url == "")
                continue;

            insertRowToRSSTable(view_feeds->item(i)->text(), url, version);
            isAddedToView = true;
            data->push_back(site_struct->initStruct(view_feeds->item(i)->text(),"RSS",url));
            data->at(data->size()-1)->setIsRead(false);
            data->at(data->size()-1)->setVersion(version);
            tp->start(site_struct);
        }
        if (!isAddedToView)
            this->close();
        return;
    }

    //remove all data from 'rss' table
    if (view_feeds->count() == 0)
    {
        while (data->size()>0)
            data->erase(0);
        removeDataFromRSSTable("", 1);
    }

    //init l_items_for_remove
    for(uint i=0; i<l_old_view_feed.size(); i++)
        l_items_for_remove.push_back(0);

    for (uint i=0;  i<view_feeds->count(); i++)
    {
        //qDebug()<<view_feeds->item(i)->text();
        for (uint j = 0; j<l_old_view_feed.size(); j++)
        {
            //qDebug()<<"COMPARING WITH: "<< l_old_view_feed[j];
            if (view_feeds->item(i)->text() == l_old_view_feed[j])
            {
                l_items_for_remove[j] = 1;
                break;
            }
            if (l_old_view_feed.size()-1 == j)
            {

                //find url and version of site_name
                QString url, version;
                findAndReturnURLAndVersion(view_feeds->item(i)->text(),url,version);
                insertRowToRSSTable(view_feeds->item(i)->text(), url, version);
                data->push_back(site_struct->initStruct(view_feeds->item(i)->text(),"RSS",url));
                data->at(data->size()-1)->setIsRead(false);
                data->at(data->size()-1)->setVersion(version);
                isAddedToView = true;
                tp->start(site_struct);
            }
        }
    }

    QList<bool> l_item_indexes_from_site_struct;
    //init l_item_indexes_from_site_struct;
    for (uint i=0; i<data->size(); i++)
        l_item_indexes_from_site_struct.push_back(1);

    //remove old items
    for (int i=0; i<l_items_for_remove.size(); i++)
        if (l_items_for_remove[i] == 0)
        {
            removeDataFromRSSTable(l_old_view_feed[i],0);
            for (uint j=0; j<data->size(); j++)
            {
                //qDebug()<<"COMPARING "<<l_old_view_feed[i]<<" WITH: "<<site_struct->s_struct[j].site_name;
                if (l_old_view_feed[i] == data->at(j)->getSiteName())
                {
                    l_item_indexes_from_site_struct[j] = 0;
                    break;
                }
            }
        }

    l_items_for_remove.swap(l_item_indexes_from_site_struct);
    if (!isAddedToView)
    {
        site_struct->isAddOption = true;
        this->close();
        vw->onUpdate(l_items_for_remove);
    }
}

//remove site_name data from 'rss' table in 'sites.db3'. If all_data == 1,
//then remove all data from 'rss' table
void OptionsWindow::removeDataFromRSSTable(QString site_name, bool all_data)
{
    db.removeDataFromRSSTable(site_name, all_data);
}

//insert row to 'rss' DB table
void OptionsWindow::insertRowToRSSTable(QString name, QString url, QString version)
{
    db.insertIntoFavoriteFeeds(name, url, version);
}

//from site_name, return url and version
void OptionsWindow::findAndReturnURLAndVersion(QString site_name, QString &url, QString &version)
{
    db.findAndReturnURLAndVersion(site_name, url, version);
}

void OptionsWindow::updateFiltersTable()
{
    bool changes = false;
    QList<QString> l_items_for_remove;
    if (l_old_filters.size()==0)
    {
        for (int i=0;  i<lw_filter_list->count(); i++)
        {
            insertRowToFiltersTable(lw_filter_list->item(i)->text());
            vw->l_filters.append(lw_filter_list->item(i)->text());
            changes = true;
        }

        if (changes)
            vw->initTextBrowser();

        return;
    }

    //remove entire data from 'filters' table
    if (lw_filter_list->count() == 0)
    {
        if (l_old_filters.size()>0)
        {
            removeDataFromFilters("", true);
            l_old_filters.clear();
            changes = true;
        }
        if (changes)
        {
            vw->l_filters.clear();
            vw->initTextBrowser();
        }
        return;
    }

    //init l_items_for_remove
    for(uint i=0; i<l_old_filters.size(); i++)
        l_items_for_remove.push_back(0);

    vw->l_filters.clear();
    for (int i=0;  i<lw_filter_list->count(); i++)
    {
        for (uint j = 0; j<l_old_filters.size(); j++)
        {
            if (lw_filter_list->item(i)->text() == l_old_filters[j])
            {
                l_items_for_remove[j] = 1;
                break;
            }
            if (l_old_filters.size()-1 == j)
            {
                insertRowToFiltersTable(lw_filter_list->item(i)->text());
                changes = true;
            }
        }
        vw->l_filters.append(lw_filter_list->item(i)->text());
    }

    //remove old items
    for (int i=0; i<l_items_for_remove.size(); i++)
        if (l_items_for_remove[i] == 0)
        {
            removeDataFromFilters(l_old_filters[i], false);
            changes = true;
        }
    if (changes)
        vw->initTextBrowser();
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
    sb_refresh_time->setValue(i);

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
        cb_enable_notification->setChecked(false);
    else if (line[21] == '1')
        cb_enable_notification->setChecked(true);
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
        cb_enable_proxy->setChecked(false);
        l_proxy_url->setEnabled(false);
        l_proxy_port->setEnabled(false);
        te_proxy_url->setEnabled(false);
        te_proxy_port->setEnabled(false);
    }
    else if (line[15] == '1')
    {
        cb_enable_proxy->setChecked(true);
        l_proxy_url->setEnabled(true);
        l_proxy_port->setEnabled(true);
        te_proxy_url->setEnabled(true);
        te_proxy_port->setEnabled(true);
    }
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from a \'Options\' file!");

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

    te_proxy_url->setText(str_tmp);

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

    te_proxy_port->setText(str_tmp);

    file.close();
}

//save options in 'Options' file
void OptionsWindow::saveOptions()
{
    QFile file("../resouce/Options");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "Refresh time: " << QString::number(sb_refresh_time->value()) <<'\n';
    site_struct->setRefreshTime(sb_refresh_time->value());

    if (cb_enable_notification->isChecked())
    {
        out << "Notification window: 1\n";
        site_struct->setEnableNotificationWindow(1);
    }
    else
    {
        out << "Notification window: 0\n";
        site_struct->setEnableNotificationWindow(0);
    }

    if (cb_enable_proxy->isChecked())
    {
        out << "Enabled Proxy: 1\n";
        site_struct->enabled_proxy_connection = 1;
    }
    else
    {
        out << "Enabled Proxy: 0\n";
        site_struct->enabled_proxy_connection = 0;
    }

    out<<"Proxy Address: "<< te_proxy_url->toPlainText()<<"\n";
    site_struct->proxy_url = te_proxy_url->toPlainText();
    out<<"Proxy Port: "<< te_proxy_port->toPlainText()<<"\n";
    site_struct->proxy_port = te_proxy_port->toPlainText();

    file.close();
}

//update collect_feeds (QListWidget var)
void OptionsWindow::updateCollectFeedListView()
{
    if (collect_feeds->count() == 0)
    {
        for (uint i=0; i<l_old_collect_feed.size(); i++)
            removeDataFromCollectFeeds(l_old_collect_feed[i]);
        return;
    }

    for (uint i=0; i<l_old_collect_feed.size(); i++)
    {
        for (int j=0; j<collect_feeds->count(); j++)
        {
            if (l_old_collect_feed[i] == collect_feeds->item(j)->text())
                break;
            if (j==collect_feeds->count()-1)
                removeDataFromCollectFeeds(l_old_collect_feed[i]);
        }
    }
}

//fill collect_feed (QListWidget)
void OptionsWindow::fillCollectListView()
{
    boost::ptr_vector<QString>tmp;
    db.getCollectFeeds(&tmp);

    l_old_collect_feed.clear();

    boost::ptr_vector<QString>::iterator it;

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        collect_feeds->insertItem(collect_feeds->count(), *it);
        l_old_collect_feed.push_back(new QString(*it));
    }
}

void OptionsWindow::fillFilterListView()
{
    boost::ptr_vector <QString> tmp;
    db.getFilterList(&tmp);

    l_old_filters.clear();

    boost::ptr_vector <QString>::iterator it;

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        addStringToFilterList(*it);
        l_old_filters.push_back(new QString(*it));
    }
}

//resize window event
void OptionsWindow::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);

    ui->treeWidget->setGeometry(5,5, 130, this->height()- (15 + ui->OK_Button->height()));
    ui->Cancel_Button->setGeometry(this->width() - (5+ui->Cancel_Button->width()),this->height() - (5+ ui->Cancel_Button->height()), ui->Cancel_Button->width(), ui->Cancel_Button->height());
    ui->OK_Button->setGeometry(ui->Cancel_Button->x()-(5+ui->OK_Button->width()),ui->Cancel_Button->y(), ui->OK_Button->width(), ui->OK_Button->height());
    download_feed_status->setGeometry(5,this->height() - (5+ ui->OK_Button->height()),download_feed_status->width(), download_feed_status->height());

    if (options_type == 1)
    {
        int width = (this->width() - (25 + ui->treeWidget->width() + ui->pushButton->width()))/2;
        collect_feeds->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, cf_find_feed->height()+10, width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));
        ui->pushButton_3->setGeometry(collect_feeds->x(),collect_feeds->y() + collect_feeds->height() + 5,  ui->pushButton_3->width(), ui->pushButton_3->height());
        cf_label_search->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, 5, 50, cf_label_search->height());
        cf_find_feed->setGeometry(cf_label_search->x() + cf_label_search_width()+5, 5,width - (cf_label_search_width() + 5) , cf_find_feed->height());
        ui->pushButton->setGeometry(collect_feeds->x()+ collect_feeds->width() +  5, (ui->pushButton_3->height()+10) + (collect_feeds->height()/2 - ( ui->pushButton->height() + ui->pushButton_2->height() + 10)/2),ui->pushButton->width(), ui->pushButton->height());
        ui->pushButton_2->setGeometry(ui->pushButton->x(), ui->pushButton->y() + ui->pushButton->height()+10, ui->pushButton_2->width(), ui->pushButton_2->height());
        view_feeds->setGeometry(ui->pushButton->x() + ui->pushButton->width() + 5,cf_find_feed->height()+10 ,width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));
    }
    else if (options_type == 2)
    {
        te_add_filter->setGeometry(pb_add_filter->x() + pb_add_filter->width() + 5,5,this->width() - (pb_add_filter->x() + pb_add_filter->width() + 10), te_add_filter->height());
        lw_filter_list->setGeometry(te_add_filter->x(), l_filter_list->y()+l_filter_list->height()+5, this->width() - (l_filter_list->x()+5), this->height() - (l_filter_list->y()+ l_filter_list->height()+15+ ui->OK_Button->height()));
    }
}

//show event
void OptionsWindow::showEvent(QShowEvent *event)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadOptions();

    download_feed_status->hide();
    collect_feeds->clear();
    view_feeds->clear();
    lw_filter_list->clear();
    fillCollectListView();
    fillViewListView();
    fillFilterListView();
    this->setEnabled(true);
}

//'>>' button has been clicked
void OptionsWindow::on_pushButton_clicked()
{
    QList<QListWidgetItem*> l;
    l = collect_feeds->selectedItems();
    if (l.size()==0)
        return;

    for(int i=0; i<l.size(); i++)
        addStringToViewList(l[i]->text());
}

//'<<' button has been clicked
void OptionsWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem*> l;
    l = view_feeds->selectedItems();
    if (l.size()==0)
        return;

    for (int i=l.size()-1; i>=0; i--)
        delete l[i];
}

//'OK' button event
void OptionsWindow::on_OK_Button_clicked()
{
    download_feed_status->show();
    this->setEnabled(false);
    saveOptions();
    site_struct->setProxySettings();
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
    if (collect_feeds->currentItem()==NULL)
        return;

    //remove from list widget
    QList<QListWidgetItem*> l;
    l = collect_feeds->selectedItems();
    if (l.size()==0)
        return;

    //remove item(s) from collect_feeds
    for (int i=l.size()-1; i>=0; i--)
    {
        for (int j = 0; j<view_feeds->count(); j++)
        {
            QListWidgetItem *item = view_feeds->item(j);
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
        options_type = 1;
        int width = (this->width() - (25 + ui->treeWidget->width() + ui->pushButton->width()))/2;
        collect_feeds->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, cf_find_feed->height()+10, width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));
        ui->pushButton_3->setGeometry(collect_feeds->x(), collect_feeds->y() + collect_feeds->height() + 5,  ui->pushButton_3->width(), ui->pushButton_3->height());
        cf_label_search->setGeometry(ui->treeWidget->x() + ui->treeWidget->width()  + 5, 5, 50, cf_label_search->height());
        cf_find_feed->setGeometry(cf_label_search->x() + cf_label_search_width()+5, 5,width - (cf_label_search_width() + 5) , cf_find_feed->height());
        ui->pushButton->setGeometry(collect_feeds->x()+ collect_feeds->width() +  5, (ui->pushButton_3->height()+10) + (collect_feeds->height()/2 - ( ui->pushButton->height() + ui->pushButton_2->height() + 10)/2),ui->pushButton->width(), ui->pushButton->height());
        ui->pushButton_2->setGeometry(ui->pushButton->x(), ui->pushButton->y() + ui->pushButton->height()+10, ui->pushButton_2->width(), ui->pushButton_2->height());
        view_feeds->setGeometry(ui->pushButton->x() + ui->pushButton->width() + 5,cf_find_feed->height()+10 ,width, this->height()-(20 +cf_find_feed->height() + ui->OK_Button->height()));

        collect_feeds->show();
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        view_feeds->show();
        cf_find_feed->show();
        cf_label_search->show();

        sb_refresh_time->hide();
        l_refresh_time->hide();
        cb_enable_notification->hide();

        cb_enable_proxy->hide();
        l_proxy_url->hide();
        l_proxy_port->hide();
        te_proxy_url->hide();
        te_proxy_port->hide();

        pb_add_filter->hide();
        te_add_filter->hide();
        lw_filter_list->hide();
        l_filter_list->hide();
        pb_remove_filter->hide();
    }
    else if (t == "Filters")
    {
        pb_add_filter->show();
        te_add_filter->show();
        lw_filter_list->show();
        l_filter_list->show();
        pb_remove_filter->show();

        options_type = 2;
        collect_feeds->hide();
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        view_feeds->hide();
        cf_find_feed->hide();
        cf_label_search->hide();

        sb_refresh_time->hide();
        l_refresh_time->hide();
        cb_enable_notification->hide();

        cb_enable_proxy->hide();
        l_proxy_url->hide();
        l_proxy_port->hide();
        te_proxy_url->hide();
        te_proxy_port->hide();

    }
    else if (t == "Notifications")
    {
        options_type = 3;

        sb_refresh_time->show();
        l_refresh_time->show();
        cb_enable_notification->show();

        collect_feeds->hide();
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        view_feeds->hide();
        cf_find_feed->hide();
        cf_label_search->hide();

        cb_enable_proxy->hide();
        l_proxy_url->hide();
        l_proxy_port->hide();
        te_proxy_url->hide();
        te_proxy_port->hide();


        pb_add_filter->hide();
        te_add_filter->hide();
        lw_filter_list->hide();
        l_filter_list->hide();
        pb_remove_filter->hide();
    }
    else if (t == "Proxy connection")
    {

        cb_enable_proxy->show();
        l_proxy_url->show();
        l_proxy_port->show();
        te_proxy_url->show();
        te_proxy_port->show();

        options_type = 4;
        collect_feeds->hide();
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        view_feeds->hide();
        cf_find_feed->hide();
        cf_label_search->hide();

        sb_refresh_time->hide();
        l_refresh_time->hide();
        cb_enable_notification->hide();


        pb_add_filter->hide();
        te_add_filter->hide();
        lw_filter_list->hide();
        l_filter_list->hide();
        pb_remove_filter->hide();
    }
}

void OptionsWindow::on_cb_enable_proxy_clicked(bool state)
{
    if (state)
    {
        l_proxy_url->setEnabled(true);
        l_proxy_port->setEnabled(true);
        te_proxy_url->setEnabled(true);
        te_proxy_port->setEnabled(true);
    }
    else
    {
        l_proxy_url->setEnabled(false);
        l_proxy_port->setEnabled(false);
        te_proxy_url->setEnabled(false);
        te_proxy_port->setEnabled(false);
    }
}

void OptionsWindow::on_pb_add_filter_clicked()
{
    if (addStringToFilterList(te_add_filter->toPlainText()))
    {
        te_add_filter->setText("");
        return;
    }
    te_add_filter->setText("");
}

//remove selected item in filter option
void OptionsWindow::on_pb_remove_filter()
{
    if (lw_filter_list->currentItem()==NULL)
        return;

    QList<QListWidgetItem*> l;
    l = lw_filter_list->selectedItems();
    if (l.size()==0)
        return;

    delete l[0];
}

void OptionsWindow::insertRowToFiltersTable(QString filter_name)
{
    db.insertRowToFiltersTable(filter_name);
}

void OptionsWindow::removeDataFromFilters(QString filter_name, bool all_data)
{
    db.removeDataFromFilters(filter_name, all_data);
}

void OptionsWindow::removeDataFromCollectFeeds(QString site_name)
{
    db.removeDataFromCollectFeeds(site_name);
}

//Filter option: adding string to filter list
int OptionsWindow::addStringToFilterList(QString cur_text)
{
    int count = lw_filter_list->count(); //get count of listWidget
    if (cur_text=="")
        return 1;

    //check for identical string
    for(int row = 0; row < lw_filter_list->count(); row++)
    {
        QListWidgetItem *item = lw_filter_list->item(row);
        // process item
        if (cur_text == item->text())
            return 1;
    }

    lw_filter_list->insertItem(count, cur_text); //insert new element in the end of list widget
    return 0;
}

void OptionsWindow::on_textChanged(QString text) //cf_find_feeds text changed event
{
    boost::ptr_vector<QString> tmp;
    db.getCollectFeedsThatContainingText(text, &tmp);

    collect_feeds->clear();

    boost::ptr_vector<QString>::iterator it;
    for (it = tmp.begin(); it!=tmp.end(); ++it)
        addStringToWatchList(*it);
}

int OptionsWindow::cf_label_search_width()
{
    QFontMetrics fm(cf_label_search->font());
    QRect rect = fm.boundingRect(cf_label_search->text());

    return rect.width();
}

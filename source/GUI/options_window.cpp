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

#include "options_window.h"


OptionsWindow::OptionsWindow(QWidget *parent) :
    QWidget(parent)
    , cb_enable_filtering_ (std::make_shared<QCheckBox>(this))
    , cb_enable_notification_(std::make_shared<QCheckBox>(this))
    , cb_enable_proxy_ (std::make_shared<QCheckBox>(this))
    , cf_find_feed_ (std::make_shared<QLineEdit> (this))
    , cf_label_search_ (std::make_shared<QLabel>(this))
    , download_feed_status_ (std::make_shared<QLabel>(this))
    , feed_list_  (std::make_shared<QListWidget>(this))
    , l_filter_list_ (std::make_shared<QLabel>(this))
    , l_proxy_url_ (std::make_shared<QLabel>(this))
    , l_proxy_port_ (std::make_shared<QLabel> (this))
    , l_refresh_time_ (std::make_shared<QLabel>(this))
    , lw_filter_list_ (std::make_shared<QListWidget>(this))
    , options_type_ (1)
    , pb_add_filter_ (std::make_shared<QPushButton>(this))
    , pb_remove_filter_ (std::make_shared<QPushButton>(this))
    , sb_refresh_time_ (std::make_shared<QSpinBox> (this))
    , te_proxy_url_ (std::make_shared<QTextEdit>(this))
    , te_proxy_port_ (std::make_shared<QTextEdit>(this))
    , te_add_filter_ (std::make_shared<QTextEdit>(this))
    , ui_(std::make_shared<Ui::OptionsWindow> ())
{

    setupGui();
}

OptionsWindow::~OptionsWindow()
{
    l_old_feed_list_.clear();
    l_old_filters_.clear();
}

//modify label string to fit in the window size
void OptionsWindow::returnModifedString(QString &str)
{
    QRect rect;
    QFontMetrics fm(download_feed_status_->font());
    QString str_tmp = str, add_str="";
    int pixel_width = 0, dots_width=0, window_width = 0;
    window_width = ui_->cancelButton->x() - 10;

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

//add an item to tree widget
void OptionsWindow::addItem(const QString &name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    ui_->treeWidget->addTopLevelItem(item);
}

//fill feed_list_ (QListWidget var)
void OptionsWindow::fillFeedListView()
{
    std::vector<QString> tmp;
    data_base_.getFeeds(&tmp);

    l_old_feed_list_.clear();

    for (unsigned int i=0; i<tmp.size(); i++)
    {
        feed_list_->insertItem(feed_list_->count(), tmp[i]);
        l_old_feed_list_.push_back(tmp[i]);
    }
}

//add string to feed_list (QListWidget var)
int OptionsWindow::addToFeedList(const QString &cur_text)
{
    int count = feed_list_->count(); //get count of listWidget
    if (cur_text=="")
    {
        return 1;
    }

    //check for identical strings
    for(int row = 0; row < feed_list_->count(); row++)
    {
        QListWidgetItem *item = feed_list_->item(row);
        if (cur_text == item->text())
        {
            return 1;
        }
    }

    feed_list_->insertItem(count, cur_text); //insert new element in the end of list widget

    return 0;
}

//remove site_name data from 'rss' table in 'sites.db3'. If all_data == 1,
//then remove all data from 'rss' table
void OptionsWindow::removeDataFromRSSTable(const QString &site_name, const bool all_data)
{
    data_base_.removeDataFromRSSTable(site_name, all_data);
}

//insert row to 'rss' DB table
void OptionsWindow::insertRowToRSSTable(const QString &name, const QString &url, const QString &version)
{
    data_base_.insertIntoFeedList(name, url, version);
}

void OptionsWindow::updateFiltersTable()
{
     //main_window_->filters_qlist.clear();
     data_base_.removeDataFromFilters(); //delete all old filters data

     for (int i=0;  i<lw_filter_list_->count(); i++)
     {
         insertRowToFiltersTable(lw_filter_list_->item(i)->text());
     }
}


void OptionsWindow::loadSettings()
{
    sb_refresh_time_->setValue(Jelyazka::Settings::getRefreshFeedsTime());
    cb_enable_notification_->setChecked(Jelyazka::Settings::getIsNotificationsEnabled());

    //proxy settings
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        cb_enable_proxy_->setChecked(false);
        l_proxy_url_->setEnabled(false);
        l_proxy_port_->setEnabled(false);
        te_proxy_url_->setEnabled(false);
        te_proxy_port_->setEnabled(false);
    }
    else
    {
        cb_enable_proxy_->setChecked(true);
        l_proxy_url_->setEnabled(true);
        l_proxy_port_->setEnabled(true);
        te_proxy_url_->setEnabled(true);
        te_proxy_port_->setEnabled(true);
    }
    te_proxy_url_->setText(Jelyazka::Settings::getProxyIpAddress());
    te_proxy_port_->setText(Jelyazka::Settings::getProxyPort());

    //filters
    if (Jelyazka::Settings::getIsFilteringEnabled())
    {
        cb_enable_filtering_->setChecked(false);
        pb_add_filter_->setEnabled(false);
        te_add_filter_->setEnabled(false);
        lw_filter_list_->setEnabled(false);
        l_filter_list_->setEnabled(false);
        pb_remove_filter_->setEnabled(false);
    }
    else
    {
        cb_enable_filtering_->setChecked(true);
        pb_add_filter_->setEnabled(true);
        te_add_filter_->setEnabled(true);
        lw_filter_list_->setEnabled(true);
        l_filter_list_->setEnabled(true);
        pb_remove_filter_->setEnabled(true);
    }

    //ToDo: add notification window
}

void OptionsWindow::saveSettings()
{
    Jelyazka::Settings::setRefreshFeedsTime(sb_refresh_time_->value());
    Jelyazka::Settings::setIsNotificationsEnabled(cb_enable_notification_->isChecked());
    Jelyazka::Settings::setIsProxyConnectionEnabled(cb_enable_proxy_->isChecked());
    Jelyazka::Settings::setProxyPort(te_proxy_port_->toPlainText());
    Jelyazka::Settings::setProxyIpAddress(te_proxy_url_->toPlainText());
    Jelyazka::Settings::setIsFilteringEnabled(cb_enable_filtering_->isChecked());
}


void OptionsWindow::fillFilterListView()
{
    std::vector <QString> tmp;
    data_base_.getFilterList(&tmp);

    l_old_filters_.clear();

    for (unsigned int i=0; i<tmp.size(); i++)
    {
        addStringToFilterList(tmp[i]);
        l_old_filters_.push_back(tmp[i]);
    }
}

void OptionsWindow::positioningFeedsOptionWidgets()
{
    int width = (this->width() - (25 + ui_->treeWidget->width()));

    cf_label_search_->setGeometry(ui_->treeWidget->x() + ui_->treeWidget->width()  + 5,
                                 5,
                                 50,
                                 cf_label_search_->height());

    cf_find_feed_->setGeometry(cf_label_search_->x() + cf_label_search_width()+5,
                              5,
                              width - (cf_label_search_width() + 5) ,
                              cf_find_feed_->height());

    feed_list_->setGeometry(cf_label_search_->x(),
                            cf_find_feed_->y() + cf_find_feed_->height()+10,
                            width,
                            this->height()-(20 +cf_find_feed_->height() + ui_->okButton->height()));

    ui_->removeButton->setGeometry(feed_list_->x(),
                                  ui_->okButton->y(),
                                  ui_->removeButton->width(),
                                  ui_->removeButton->height());
}

//resize window event
void OptionsWindow::resizeEvent(QResizeEvent *event)
{

    QWidget::resizeEvent(event);

    ui_->treeWidget->setGeometry(5,5, 130, this->height()- (15 + ui_->okButton->height()));

    ui_->cancelButton->setGeometry(this->width() - (5+ui_->cancelButton->width()),
            this->height() - (5+ ui_->cancelButton->height()),
            ui_->cancelButton->width(),
            ui_->cancelButton->height());

    ui_->okButton->setGeometry(ui_->cancelButton->x()-(5+ui_->okButton->width()),
                                ui_->cancelButton->y(),
                                ui_->okButton->width(),
                                ui_->okButton->height());

    download_feed_status_->setGeometry(5,
                                      this->height() - (5+ ui_->okButton->height()),
                                      download_feed_status_->width(),
                                      download_feed_status_->height());

    if (options_type_ == 1)
    {
        positioningFeedsOptionWidgets();
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
                                    this->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ui_->okButton->height()));
    }
}

//show event
void OptionsWindow::showEvent(QShowEvent *event)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadSettings();

    download_feed_status_->hide();
    feed_list_->clear();
    lw_filter_list_->clear();
    fillFeedListView();
    fillFilterListView();

    this->setEnabled(true);
}

//'Remove' button click event
void OptionsWindow::on_removeButton_clicked()
{
    //get selected items
    QModelIndexList list =feed_list_->selectionModel()->selectedIndexes();
    QStringList slist;
    foreach(const QModelIndex &index, list){
        slist.append( index.data(Qt::DisplayRole ).toString());
        feed_list_->takeItem(index.row());
    }

    //remove selected items from db
    for (int i=0; i< slist.size(); ++i)
    {
        data_base_.removeDataFromFeedList(slist.at(i));
    }
}

//'OK' button event
void OptionsWindow::on_okButton_clicked()
{
    download_feed_status_->show();
    this->setEnabled(false); //it's gray out the "Option Window"
    saveSettings(); //save current options in a file

    updateFiltersTable();
    emit (stateChanged("UpdatingSettings"));
}

//'Cancel' button has been clicked
void OptionsWindow::on_cancelButton_clicked()
{
    emit (stateChanged("HideOptionWindow"));
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
    {
        return;
    }

    QList<QListWidgetItem*> l;
    l = lw_filter_list_->selectedItems();
    if (l.size()==0)
    {
        return;
    }

    delete l[0];
}

void OptionsWindow::insertRowToFiltersTable(const QString &filter_name)
{
    data_base_.insertRowToFiltersTable(filter_name);
}

//Filter option: adding string to filter list
int OptionsWindow::addStringToFilterList(const QString &cur_text)
{
    int count = lw_filter_list_->count(); //get count of listWidget
    if (cur_text=="")
    {
        return 1;
    }

    //check for identical string
    for(int row = 0; row < lw_filter_list_->count(); row++)
    {
        QListWidgetItem *item = lw_filter_list_->item(row);
        // process item
        if (cur_text == item->text())
        {
            return 1;
        }
    }

    lw_filter_list_->insertItem(count, cur_text); //insert new element in the end of list widget
    return 0;
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
    positioningFeedsOptionWidgets();

    ui_->removeButton->show();
    feed_list_->show();
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
    ui_->removeButton->hide();
    feed_list_->hide();
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

void OptionsWindow::closeEvent (QCloseEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    event->ignore();
    emit (stateChanged("HideOptionWindow"));
}


void OptionsWindow::setupGui ()
{
    ui_->setupUi(this);

    ui_->treeWidget->setHeaderLabel("Options");

    addItem("Manage feeds");
    addItem("Filters");
    addItem("Notifications");
    addItem("Proxy connection");


    download_feed_status_->setGeometry(5,
                                      this->height() - (5+ ui_->okButton->height()),
                                      download_feed_status_->width(),
                                      download_feed_status_->height());

    //treewidget set geometry
    ui_->treeWidget->setGeometry(5,
                                5,
                                130,
                                this->height()- (15 + ui_->okButton->height()));
    ui_->cancelButton->setGeometry(this->width() - (5+ui_->cancelButton->width()),
                                   this->height() - (5+ ui_->cancelButton->height()),
                                   ui_->cancelButton->width(),
                                   ui_->cancelButton->height());
    ui_->okButton->setGeometry(ui_->cancelButton->x()-(5+ui_->okButton->width()),
                               ui_->cancelButton->y(),
                               ui_->okButton->width(),
                               ui_->okButton->height());

    //Collection feeds controls
    feed_list_->setSelectionMode(QAbstractItemView::MultiSelection);

    connect(cf_find_feed_.get(),SIGNAL(textChanged(QString)), this, SLOT(on_textChanged(QString)));

    cf_label_search_->setText("Search");
    positioningFeedsOptionWidgets();

    feed_list_->show();
    cf_find_feed_->show();
    cf_label_search_->show();

    //notification widgets
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
    cb_enable_proxy_->setChecked(false);
    cb_enable_proxy_->setText("Enable proxy connection");
    connect(cb_enable_proxy_.get(), SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_proxy_clicked(bool)));
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
                                 this->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ui_->okButton->height()));
    pb_remove_filter_->setGeometry(ui_->treeWidget->width()+10,
                                  lw_filter_list_->y(),
                                  pb_remove_filter_->width(),
                                  pb_remove_filter_->height());

    cb_enable_filtering_->setChecked(false);
    cb_enable_filtering_->setText("Enable filtering");
    pb_add_filter_->setText("Add");
    pb_remove_filter_->setText("Remove");
    l_filter_list_->setText("Filter List:");

    connect(cb_enable_filtering_.get(), SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_filtering_clicked(bool)));
    connect(pb_add_filter_.get(), SIGNAL(clicked()), this, SLOT(on_pb_add_filter_clicked()));
    connect(pb_remove_filter_.get(), SIGNAL(clicked()), this, SLOT(on_pb_remove_filter()));

    cb_enable_filtering_->hide();
    pb_add_filter_->hide();
    te_add_filter_->hide();
    lw_filter_list_->hide();
    l_filter_list_->hide();
    pb_remove_filter_->hide();
}

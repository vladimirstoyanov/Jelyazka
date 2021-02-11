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
    //, cb_enable_filtering_ (std::make_shared<QCheckBox>(this))
    //, cb_enable_notification_(std::make_shared<QCheckBox>(this))
    //, cb_enable_proxy_ (std::make_shared<QCheckBox>(this))
    //, cf_find_feed_ (std::make_shared<QLineEdit> (this))
    //, cf_label_search_ (std::make_shared<QLabel>(this))
    , download_feed_status_ (std::make_shared<QLabel>(this))
    //, feed_list_  (std::make_shared<QListWidget>(this))
    //, l_filter_list_ (std::make_shared<QLabel>(this))
    //, l_proxy_url_ (std::make_shared<QLabel>(this))
    //, l_proxy_port_ (std::make_shared<QLabel> (this))
    //, l_refresh_time_ (std::make_shared<QLabel>(this))
    //, lw_filter_list_ (std::make_shared<QListWidget>(this))
    , options_type_ (1)
    //, pb_add_filter_ (std::make_shared<QPushButton>(this))
    //, pb_remove_filter_ (std::make_shared<QPushButton>(this))
    //, sb_refresh_time_ (std::make_shared<QSpinBox> (this))
    //, te_proxy_url_ (std::make_shared<QTextEdit>(this))
    //, te_proxy_port_ (std::make_shared<QTextEdit>(this))
    //, te_add_filter_ (std::make_shared<QTextEdit>(this))
    , ui_(std::make_shared<Ui::OptionsWindow> ())
{

    setupGui();
}

OptionsWindow::~OptionsWindow()
{
    //l_old_feed_list_.clear();
    //l_old_filters_.clear();
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

/*void OptionsWindow::fillFeedListView()
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
*/
/*
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
*/

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


void OptionsWindow::loadSettings()
{
    //sb_refresh_time_->setValue(Jelyazka::Settings::getRefreshFeedsTime());
    //cb_enable_notification_->setChecked(Jelyazka::Settings::getIsNotificationsEnabled());
    /*
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
    */
    /*
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
    */
    for (unsigned int i=0; i<options.size(); ++i)
    {
        options[i]->loadSettings();
    }

    //ToDo: add notification window
}

void OptionsWindow::saveSettings()
{
    for (unsigned int i=0; i<options.size(); ++i)
    {
        options[i]->saveSettings();
    }
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
        options[0]->resize();
    }
    else if (options_type_ == 2)
    {
        options[1]->resize();
    }
}

//show event
void OptionsWindow::showEvent(QShowEvent *event)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadSettings();

    download_feed_status_->hide();

    for (unsigned int i=0; i<options.size(); ++i)
    {
        options[i]->initilize();
    }

    this->setEnabled(true);
}

//'OK' button event
void OptionsWindow::on_okButton_clicked()
{
    download_feed_status_->show();
    this->setEnabled(false); //it's gray out the "Option Window"
    saveSettings(); //save current options in a file

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
    int row = index.row();
    options[row]->show();

    for (unsigned int i=0; i<options.size(); ++i)
    {
        if (row==i)
        {
            continue;
        }
        options[i]->hide();
    }
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

    std::shared_ptr<IOptions> feedsOptions = std::make_shared<FeedsOptions> (this,
                                                                                 ui_->treeWidget->x() + ui_->treeWidget->width(),
                                                                                 ui_->okButton->height());
    std::shared_ptr<IOptions> filtersOptions = std::make_shared<FiltersOptions> (this,
                                                                                 ui_->treeWidget->x() + ui_->treeWidget->width(),
                                                                                 ui_->okButton->height());
    std::shared_ptr<IOptions> notificationsOptions = std::make_shared<NotificationsOptions> (this,
                                                                                 ui_->treeWidget->x() + ui_->treeWidget->width(),
                                                                                 ui_->okButton->height());
    std::shared_ptr<IOptions> proxyOptions = std::make_shared<ProxyOptions> (this,
                                                                                 ui_->treeWidget->x() + ui_->treeWidget->width(),
                                                                                 ui_->okButton->height());
    options.push_back(feedsOptions);
    options.push_back(filtersOptions);
    options.push_back(notificationsOptions);
    options.push_back(proxyOptions);

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

    for (unsigned int i=0; i<options.size(); ++i)
    {
        options[i]->setupGui();
    }
}

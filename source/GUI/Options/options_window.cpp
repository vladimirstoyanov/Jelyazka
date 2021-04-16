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
    , download_feed_status_ (std::make_shared<QLabel>(this))
    , offset_between_widgets_ (5)
    , ui_(std::make_shared<Ui::OptionsWindow> ())
{
    setupGui();
}

OptionsWindow::~OptionsWindow()
{
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

//add an item to 'treeWidget'
void OptionsWindow::addItemToTreeView(const QString &name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0,name);
    ui_->treeWidget->addTopLevelItem(item);
}

void OptionsWindow::insertRowToRSSTable(const QString &name, const QString &url, const QString &version)
{
    data_base_.insertIntoFeedList(name, url, version);
}

void OptionsWindow::loadSettings()
{
    for (auto option: options)
    {
        option->loadSettings();
    }
}

void OptionsWindow::saveSettings()
{
    for (auto option: options)
    {
        option->saveSettings();
    }

    Jelyazka::Settings::saveSettings();
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

    for (auto option: options)
    {
        option->resize();
    }
}

//show event
void OptionsWindow::showEvent(QShowEvent *event)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    loadSettings();

    download_feed_status_->hide();

    for (auto option: options)
    {
         option->initilize();
    }

    this->setEnabled(true);
}

//'OK' button clicked event
void OptionsWindow::on_okButton_clicked()
{
    download_feed_status_->show();
    this->setEnabled(false); //gray out the "Option Window"
    saveSettings(); //save current options in a file

    emit (stateChanged("UpdatingSettings"));
}

//'Cancel' button clicked event
void OptionsWindow::on_cancelButton_clicked()
{   
    emit (stateChanged("HideOptionWindow"));
}

//treeWidget clicked event
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

//"Option window" close event
void OptionsWindow::closeEvent (QCloseEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    event->ignore();
    emit (stateChanged("HideOptionWindow"));
}

void OptionsWindow::createOptions ()
{
    std::shared_ptr<IOptions> feedsOptions = std::make_shared<FeedsOptions> (this,
                                                                                 ui_->treeWidget->x() + ui_->treeWidget->width(),
                                                                                 ui_->okButton->height(),
                                                                                 ui_->okButton->y());
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
}

void OptionsWindow::treeWidgetSetup ()
{
    ui_->treeWidget->setHeaderLabel("Options");

    addItemToTreeView("Manage feeds");
    addItemToTreeView("Filters");
    addItemToTreeView("Notifications");
    addItemToTreeView("Proxy");

    //treewidget set geometry
    ui_->treeWidget->setGeometry(offset_between_widgets_,
                                offset_between_widgets_,
                                130,
                                this->height()- (15 + ui_->okButton->height()));
}

void OptionsWindow::widgetsSetup ()
{
    treeWidgetSetup();

    download_feed_status_->setGeometry(offset_between_widgets_,
                                      this->height() - (offset_between_widgets_+ ui_->okButton->height()),
                                      download_feed_status_->width(),
                                      download_feed_status_->height());

    ui_->cancelButton->setGeometry(this->width() - (offset_between_widgets_ +ui_->cancelButton->width()),
                                   this->height() - (offset_between_widgets_ + ui_->cancelButton->height()),
                                   ui_->cancelButton->width(),
                                   ui_->cancelButton->height());

    ui_->okButton->setGeometry(ui_->cancelButton->x()-(offset_between_widgets_+ui_->okButton->width()),
                               ui_->cancelButton->y(),
                               ui_->okButton->width(),
                               ui_->okButton->height());
}

void OptionsWindow::setupGui ()
{
    ui_->setupUi(this);

    widgetsSetup();
    createOptions();

    for (auto option: options)
    {
        option->setupGui();
    }
}

/*
    initwindow.cpp
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
#include "init_window.h"

InitWindow::InitWindow(QWidget *parent) :
    QWidget(parent)
    , data_base_ ()
    , image_init_label_ (std::make_shared <QLabel>(this))
    , init_image_ (std::make_shared<QImage>("../resources/jelyazka_02_end.png"))
    , download_rss_data_thread_ (new DownloadRssDataThread ())
    , thread_pool_(std::make_shared <QThreadPool>(this))
    , ui_(new Ui::InitWindow)
{
    qDebug()<<__PRETTY_FUNCTION__;
    setupGui();
}

InitWindow::~InitWindow()
{
    qDebug()<<__PRETTY_FUNCTION__;

    thread_pool_->waitForDone();
    //download_rss_data_thread_->deleteLater();
}

void InitWindow::setupGui()
{
    qDebug()<<__PRETTY_FUNCTION__;
    ui_->setupUi(this);

    //setting and display "Jelyazka" image to the windows
    ui_->label->setGeometry(5,260,250,40);
    ui_->label->setStyleSheet("QLabel { color : white; }");
    ui_->label->setText("");

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(30,100,300,300);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center()); //move the window to the center of the screen
    this->setStyleSheet("background-color:black;");

    image_init_label_->setPixmap(QPixmap::fromImage(*init_image_));
    image_init_label_->setGeometry(QRect(0,0,300,300));
    image_init_label_->show();
    image_init_label_->lower();
}

void InitWindow::loadRssUrls()
{
    qDebug()<<__PRETTY_FUNCTION__<<": loading RSS URLs from DB...";

    std::vector<QString> urls;
    urls = data_base_.getURLs();

    for (unsigned int i=0; i<urls.size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<urls[i];
        Feed feed;
        feed.setFeedUrl(urls[i]);
        feeds_.push_back(feed);
    }
}

void InitWindow::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    loadRssUrls();
    download_rss_data_thread_->setURLs(feeds_);


    for (unsigned int i=0; i<feeds_.size(); ++i)
    {
        thread_pool_->start(download_rss_data_thread_);
        qDebug()<<__PRETTY_FUNCTION__<<": after";
    }

    if (feeds_.size() == 0)
    {
        onDownloadFinished();
    }
}

void InitWindow::onWriteData(RSSData rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__;

    for (size_t i=0; i< rss_data.getArticlesSize(); ++i)
    {
         data_base_.insertIntoRssDataTable(rss_data.getSiteName()
                                 , rss_data.articleAt(i).getTitle()
                                 , rss_data.articleAt(i).getLink()
                                 , rss_data.articleAt(i).getText());
    }
}

void InitWindow::onDownloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    //send an event to window state machine
    this->hide();
    emit (stateChanged("RSSDataDownloaded"));
}

void InitWindow::makeConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect(download_rss_data_thread_
            , SIGNAL(writeData(RSSData))
            , this
            , SLOT(onWriteData(RSSData))
            , Qt::QueuedConnection);

    connect(download_rss_data_thread_
            , SIGNAL(downloadFinished())
            , this
            , SLOT(onDownloadFinished())
            , Qt::QueuedConnection);
}

void InitWindow::showEvent(QShowEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    makeConnections();
    loadRssFeeds();
}

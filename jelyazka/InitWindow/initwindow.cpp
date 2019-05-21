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
#include "initwindow.h"

InitWindow::InitWindow(QWidget *parent) :
    QWidget(parent)
    , data_base_ ()
    , image_init_label_ (std::make_shared <QLabel>(this))
    , init_image_ (std::make_shared<QImage>("../resources/jelyazka_02_end.png"))
    , init_window_thread_ (std::make_shared<InitWindowThread> ())
    , thread_pool_(std::make_shared <QThreadPool>(this))
    , ui_(new Ui::InitWindow)
{
    qDebug()<<__PRETTY_FUNCTION__;
    settingInitWindow();
    makeConnections();
    loadRssFeeds();
}

InitWindow::~InitWindow()
{
}

void InitWindow::settingInitWindow()
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

    std::shared_ptr<Data> feeds = std::make_shared<Data> ();
    data_base_.loadStrctureFromDB(feeds);

    for (unsigned int i=0; i<feeds->size(); ++i)
    {
        qDebug()<<"URL["<<i<<"] = "<<feeds->at(i)->getURL();
        Feed feed;
        feed.setFeedUrl(feeds->at(i)->getURL());
        feeds_.push_back(feed);
    }
}

void InitWindow::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    loadRssUrls();
    init_window_thread_->setURLs(feeds_);

    for (unsigned int i=0; i<feeds_.size(); ++i)
    {
        thread_pool_->start(init_window_thread_.get());
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
}

void InitWindow::makeConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect(init_window_thread_.get()
            , SIGNAL(writeData(RSSData))
            , this
            , SLOT(onWriteData(RSSData))
            , Qt::QueuedConnection);

    connect(init_window_thread_.get()
            , SIGNAL(downloadFinished())
            , this
            , SLOT(onDownloadFinished())
            , Qt::QueuedConnection);
}
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
    , network_manager_(std::make_shared<NetworkManager> ())
    , response_number_(0)
    , ui_(new Ui::InitWindow)
    , urls_size_ (0)
{
    qDebug()<<__PRETTY_FUNCTION__;
    setupGui();
}

InitWindow::~InitWindow()
{
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

void InitWindow::loadRssFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;

    std::vector<QString> urls;
    urls = data_base_.getURLs();
    urls_size_ = urls.size();

    for (unsigned int i=0; i<urls_size_; ++i)
    {
        emit (httpGetRequest(urls[i]));
        qDebug()<<__PRETTY_FUNCTION__<<": after";
    }

    if (0 == urls_size_)
    {
        downloadFinished();
    }
}

void InitWindow::writeData(const RSSData &rss_data)
{
    qDebug()<<__PRETTY_FUNCTION__<<":"<<rss_data.getSiteName();

    ui_->label->setText(rss_data.getSiteName());

    for (size_t i=0; i< rss_data.getArticlesSize(); ++i)
    {
         data_base_.insertIntoRssDataTable(rss_data.getSiteName()
                                 , rss_data.articleAt(i).getTitle()
                                 , rss_data.articleAt(i).getLink()
                                 , rss_data.articleAt(i).getText());
    }
}

void InitWindow::downloadFinished ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    this->hide();
    emit (stateChanged("RSSDataDownloaded"));
}

void InitWindow::setupConnections ()
{
    qDebug()<<__PRETTY_FUNCTION__;

    connect( this
            , SIGNAL(httpGetRequest(const QString &))
            , network_manager_.get()
            , SLOT(onHttpGetRequest(const QString &))
            , Qt::QueuedConnection);

    connect( network_manager_.get()
            , SIGNAL(httpRequestReceived(const HttpData))
            , this
            , SLOT(onHttpRequestReceived(const HttpData &))
            , Qt::QueuedConnection);
}


void InitWindow::onHttpRequestReceived (const HttpData & httpData)
{
    ++response_number_;
    qDebug()<<__PRETTY_FUNCTION__<<"!!!!!!!!!!!!!!!!!!!!!";
    if (httpData.isResponseSuccessful())
    {
        ParseRSS parse;
        std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData> ();
        rss_data->setURL(httpData.getUrl());

        //pasrse web content to RSSData
        parse.getRSSDataByWebSource(httpData.getData(), rss_data);
        writeData(*rss_data.get());
    }
    if (response_number_ == urls_size_)
    {
        downloadFinished();
    }
}

void InitWindow::showEvent(QShowEvent *event)
{
    qDebug()<<__PRETTY_FUNCTION__;
    setupConnections();
    loadRssFeeds();
}

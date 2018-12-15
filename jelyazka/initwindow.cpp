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
    QWidget(parent),
    ui_(new Ui::InitWindow),
    thread_pool_(new QThreadPool(this)),
    image_init_label_ (new QLabel(this)),
    init_image_ (new QImage("../resources/jelyazka_02_end.png")),
    rss_thread_(NULL),
    data_(NULL)

{
    ui_->setupUi(this);

    ui_->label->setGeometry(5,260,250,40);
    ui_->label->setStyleSheet("QLabel { color : white; }");
    ui_->label->setText("");

    this->setWindowFlags( Qt::FramelessWindowHint);
    this->setGeometry(30,100,300,300);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center()); //move the window to the center of the screen
    this->setStyleSheet("background-color:black;");

    image_init_label_->setPixmap(QPixmap::fromImage(*init_image_));
    image_init_label_->setGeometry(QRect(0,0,300,300));
    image_init_label_->show();
    image_init_label_->lower();
}

InitWindow::~InitWindow()
{
    delete ui_;
    delete init_image_;
    delete image_init_label_;
    delete thread_pool_;
}

//load RSS feeds in thread pool
void InitWindow::setSignal(RSSThread *rss_thread, Data *data)
{
    data_ = data;
    rss_thread_ = rss_thread;
    connect(rss_thread_,SIGNAL(loadRSS(QString,QString)),this,SLOT(onLoadRss(QString,QString)));

    for (unsigned int i=0; i<data_->size(); i++)
        thread_pool_->start(rss_thread_);

    if (data_->size()==0)
    {
        rss_thread_->first_load_ = true;
        this->hide();
        emit Done();
    }
    rss_thread_->setAutoDelete(true);
}
void InitWindow::onLoadRss(QString name, QString url)
{
    if (url == "" && name == "") //if loading RSS feeds finish
    {
        rss_thread_->first_load_ = true;
        this->hide();
        emit Done();
        return;
    }

    ui_->label->setText("Loading: " + name);
}

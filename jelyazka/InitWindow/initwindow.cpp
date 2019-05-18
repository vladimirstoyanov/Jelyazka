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
    , ui_(new Ui::InitWindow)
    , thread_pool_(std::make_shared <QThreadPool>(this))
    , image_init_label_ (std::make_shared <QLabel>(this))
    , init_image_ (std::make_shared<QImage>("../resources/jelyazka_02_end.png"))
    , init_window_thread_ (std::make_shared<InitWindowThread> ())
{
    qDebug()<<__PRETTY_FUNCTION__;
    settingInitWindow ();
    loadRSSFeeds();
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

    this->setWindowFlags( Qt::FramelessWindowHint);
    this->setGeometry(30,100,300,300);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center()); //move the window to the center of the screen
    this->setStyleSheet("background-color:black;");

    image_init_label_->setPixmap(QPixmap::fromImage(*init_image_));
    image_init_label_->setGeometry(QRect(0,0,300,300));
    image_init_label_->show();
    image_init_label_->lower();
}

void InitWindow::loadRSSFeeds()
{
    qDebug()<<__PRETTY_FUNCTION__;
    init_window_thread_->loadRssUrls();
    unsigned int count_urls= init_window_thread_->getFeedsCount();

    for (unsigned int i=0; i<count_urls; i++)
    {
        thread_pool_->start(init_window_thread_.get());
    }
}

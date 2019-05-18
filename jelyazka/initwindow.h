/*
    initwindow.h
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
#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <memory>

#include <QDesktopWidget>
#include <QImage>
#include <QLabel>
#include <QWidget>
#include <QThreadPool>

#include "data.h"
#include "rssthread.h"
#include "ui_initwindow.h"


namespace Ui
{
    class InitWindow;
}

class InitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = nullptr);
    virtual ~InitWindow();
    void setSignal (std::shared_ptr<RSSThread> rss_thread, std::shared_ptr<Data> data);

public slots:
    void onLoadRss(QString name, QString url);
signals:
    void Done();

private:
    std::shared_ptr<Ui::InitWindow> ui_;
    std::shared_ptr<QThreadPool> thread_pool_;
    std::shared_ptr<QLabel> image_init_label_;
    std::shared_ptr<QImage> init_image_;
    std::shared_ptr<RSSThread> rss_thread_;
    std::shared_ptr<Data> data_;
};

#endif // INITWINDOW_H

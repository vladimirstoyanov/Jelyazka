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

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QThreadPool>
#include "rssthread.h"
#include "data.h"

namespace Ui {
class InitWindow;
}

class InitWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InitWindow(QWidget *parent = 0);
    ~InitWindow();
    void setSignal (RSSThread *rss_thread, Data *data);

private:
    Ui::InitWindow *ui_;
    QThreadPool *thread_pool_;
    QLabel *image_init_label_;
    QImage *init_image_;
    RSSThread *rss_thread_;
    Data *data_;

public slots:
    void onLoadRss(QString name, QString url);
signals:
    void Done();
};

#endif // INITWINDOW_H

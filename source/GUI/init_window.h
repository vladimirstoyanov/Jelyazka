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
#include <QtDebug>
#include <QImage>
#include <QLabel>
#include <QWidget>

#include "database.h"
#include "Network/network_manager.h"
#include "Network/http_data.h"
#include "RSS/parse_rss.h"

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
    virtual  ~InitWindow();

public slots:
    void onDownloadFinished ();
    void onWriteData(const RSSData &rss_data);

private slots:
    void onHttpRequestReceived (const HttpData httpData);

signals:
    void stateChanged (const QString &event);
    void httpGetRequest (const QString &);

private:
    DataBase                            data_base_;
    std::shared_ptr<QLabel>             image_init_label_;
    std::shared_ptr<QImage>             init_image_;
    std::shared_ptr<NetworkManager>     network_manager_;
    unsigned int                        response_number_;
    std::shared_ptr<Ui::InitWindow>     ui_;
    unsigned int                        urls_size_;


private:
    void loadRssFeeds();
    void setupConnections ();
    void setupGui();
    void showEvent(QShowEvent *);
};

#endif // INITWINDOW_H

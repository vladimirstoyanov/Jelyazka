/*
    animatewindow.h
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
#ifndef ANIMATEWINDOW_H
#define ANIMATEWINDOW_H

#include <memory>

#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <QList>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QScreen>
#include <QShowEvent>
#include <QTime>
#include <QWidget>

#include "RSS/rss_data.h"
#include "ui_notificationwindow.h"

namespace Ui
{
    class NotificationWindow;
}

class RSSThread; //ToDo: remove this one

class NotificationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit NotificationWindow(QWidget *parent = 0);
    virtual ~NotificationWindow();

public slots:
    void onHideAnimationFinished();
    void onRssDataUpdated(const std::vector<RSSData> &);
    void onShowAnimationFinished();

private:
    QRect                                   begin_coordinates_;
    QImage                                  close_button_image_;
    int                                     desktop_height_;
    int                                     desktop_width_;
    QRect                                   end_coordinates_;
    std::shared_ptr<QPropertyAnimation>     hide_window_animation_;
    std::shared_ptr<QLabel>                 image_label_;
    bool                                    is_mouse_clicked_;
    bool                                    is_X_changed_;
    std::shared_ptr<QPropertyAnimation>     show_window_animation_;
    int                                     show_delay_;
    std::shared_ptr<Ui::NotificationWindow> ui_;

    void                delay(const int seconds);
    bool                eventFilter(QObject *, QEvent *);
    void                generateHtmlSource (const std::vector<RSSData> &new_articles, QString &html_source);
    void                getDesktopResolution(int& horizontal, int& vertical);
    int                 getTaskBarHeight();
    void                gradientRect(const int x, const int y, const int width, const int height);
    void                hideWindowAnimation();
    void                loadImage();
    void                mousePressEvent( QMouseEvent * e );
    void                paintEvent(QPaintEvent *);
    void                setupGui ();
    void                showEvent(QShowEvent *);
    void                showWindowAnimation();
};



#endif // ANIMATEWINDOW_H

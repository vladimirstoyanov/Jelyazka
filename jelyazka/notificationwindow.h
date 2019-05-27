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
#include <QShowEvent>
#include <QTime>
#include <QWidget>

#include "data.h"
#include "ui_notificationwindow.h"

namespace Ui
{
    class NotificationWindow;
}

class RSSThread;

class NotificationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit NotificationWindow(QWidget *parent = 0);
    virtual ~NotificationWindow();

    void setSignal(std::shared_ptr<RSSThread> rssThread , std::shared_ptr<Data> data);

public slots:
    void onHideAnimationFinished();
    void onShowAnimateWindow(QString);
    void onRssDataUpdated(std::vector<RSSData>);
    void onShowAnimationFinished();


private:
    bool eventFilter(QObject *, QEvent *);
    void mousePressEvent( QMouseEvent * e );
    void paintEvent(QPaintEvent *);
    void showEvent(QShowEvent *);

private:
    void delay(int seconds);
    void getDesktopResolution(int& horizontal, int& vertical);
    void gradientRect(int x, int y, int width, int height);
    void hideWindowAnimation();
    void showWindowAnimation();
    void LoadImage_(); //ToDo: rename this function

private:
    int getTaskBarHeight();

private:
    QList<unsigned int> getIndexes(QString data);
    std::shared_ptr<QPropertyAnimation> show_window_animation_;
    std::shared_ptr<QPropertyAnimation> hide_window_animation_;
    std::shared_ptr<QLabel> image_label_;
    QImage close_button_image_;
    std::shared_ptr<Ui::NotificationWindow> ui_;
    //std::shared_ptr<RSSThread> rss_thread_;
    bool is_mouse_clicked_; //if mouse clicked on this window, mouse_clicked = true, otherwise mouse_clicked = false;
    bool is_X_changed_; //'X' button image has been changed, then isXchanged = true, otherwise isXchanged = false;
    std::shared_ptr<Data> data_;
};



#endif // ANIMATEWINDOW_H

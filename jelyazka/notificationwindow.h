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

#include "rssthread.h"
#include <QPropertyAnimation>
#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <QShowEvent>
#include <QList>
#include <QDesktopWidget>
#include "data.h"

namespace Ui {
class NotificationWindow;
}

class RSSThread;

class NotificationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit NotificationWindow(QWidget *parent = 0);
    ~NotificationWindow();

    void setSignal(RSSThread *rssThread , Data *data);

public slots:
    void onShowAnimateWindow(QString);
    void on_animation_finished();
    void on_animation_finished2();


private:
    QPropertyAnimation *show_window_animation_;
    QPropertyAnimation *hide_window_animation_;
    QLabel *image_label_;
    QImage close_button_image_;
    Ui::NotificationWindow *ui_;
    RSSThread *rss_thread_;
    bool mouse_clicked_; //if mouse clicked on this window, mouse_clicked = true, otherwise mouse_clicked = false;
    bool is_X_changed_; //'X' button image has been changed, then isXchanged = true, otherwise isXchanged = false;
    Data *data_;


    void getDesktopResolution(int& horizontal, int& vertical);
    int getTaskBarHeight();
    QList<int> getIndexes(QString data);

    void showWindowAnimation();
    void hideWindowAnimation();
    void LoadImage_();
    void mousePressEvent( QMouseEvent * e );
    void showEvent(QShowEvent *);
    void delay(int seconds);

    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *);
    void gradientRect(int x, int y, int width, int height);

};



#endif // ANIMATEWINDOW_H

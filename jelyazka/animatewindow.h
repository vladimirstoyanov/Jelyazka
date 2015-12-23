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
class CAnimateWindow;
}

class RSSThread;

class CAnimateWindow : public QWidget
{
    Q_OBJECT
    
public:
    typedef QList<int> IndexesList; //list with indexes of the new articles from 'site_struct' instance

    explicit CAnimateWindow(QWidget *parent = 0);
    ~CAnimateWindow();

    void setSignal(RSSThread *data , Data *data_tmp);

public slots:
    void onShowAnimateWindow(QString);
    void on_animation_finished();
    void on_animation_finished2();
private:
    QPropertyAnimation *animation;
    QPropertyAnimation *animation2;
    QLabel *imageLabel;
    QImage close_button_img;
    Ui::CAnimateWindow *ui;
    RSSThread *site_struct;
    bool mouse_clicked; //if mouse clicked on this window, mouse_clicked = true, otherwise mouse_clicked = false;
    bool isXchanged; //'X' button image has been changed, then isXchanged = true, otherwise isXchanged = false;
    Data *data;

    void getDesktopResolution(int& horizontal, int& vertical);
    int getTaskBarHeight();
    QList<int> getIndexes(QString data);
    void animate(); //show animation
    void animate2(); //hide animation
    void LoadImage_();
    void mousePressEvent( QMouseEvent * e );
    void showEvent(QShowEvent *);
    void delay(int seconds);

    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *);
    void gradientRect(int x, int y, int width, int height);

};



#endif // ANIMATEWINDOW_H

/*
    viewwindow.h
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
#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QDesktopWidget>
#include <QWidget>
#include <QCloseEvent>
#include <QShowEvent>
#include <QResizeEvent>
#include <QLabel>
#include "rssthread.h"
#include "search.h"
#include "http.h"
#include <QMouseEvent>
#include <QEvent>
#include "rsssearchgui.h"
#include <QPainter>
#include "Options/optionswindow.h"
#include <qsizegrip.h>
#include <QStringList>
#include <QList>
#include "help.h"
#include "database.h"
//#include "rssarticle.h"
#include "data.h"

namespace Ui {
class ViewWindow;
}

class RSSSearchGUI;
class OptionsWindow;

class ViewWindow : public QWidget
{
    Q_OBJECT
    
public:
    QList<QString> filters_qlist; //ToDo: move it to the private section

    explicit ViewWindow(QWidget *parent = 0, RSSThread *rss_thread=NULL, Data *data=NULL);
    ~ViewWindow();

    void initDataInComboBoxFromStructure();
    void initTextBrowser();
    void onUpdate(QList<bool> l_removed_items);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    ulong current_site_index_;
    ulong current_article_index_;
    Ui::ViewWindow *ui_;
    RSSThread *rss_thread_;
    QLabel *image_add_rss_label_;
    QImage add_rss_button_image_;
    QLabel *image_options_label_;
    QImage options_button_image_;
    QLabel *image_refresh_label_;
    QImage refresh_button_image_;
    QLabel *image_help_label_;
    QImage help_button_image_;
    QLabel *image_X_label_;
    QImage x_button_image_;
    QLabel *image_minimize_label_;
    QImage minimize_button_image_;
    QLabel *image_maximize_label_;
    QImage maximize_button_image_;
    RSSSearchGUI *wsi_;
    OptionsWindow *ow_;
    //QSizeGrip *size_grip;
    QRect old_size_;
    Help *help_gui_;
    bool is_show_flag_;
    bool is_resizing_;
    bool is_minimize_;
    bool is_close_;
    DataBase data_base;
    int width_;
    int height_;
    bool is_X_changed_;
    bool is_minimize_changed_;
    bool is_maximize_changed_;
    bool is_flag_maximized_;
    bool is_press_released_;
    QPoint cur_point_;
    QPoint move_point_pos_;
    QPoint resize_point_;
    Data *data_;

    void initDataInComboBox();
    void addToCombobox(QString str);
    int showArticle(int struct_index, int article_index);
    void closeEvent(QCloseEvent *); // Overriding the window's close event
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *, QEvent *);
    void paintEvent(QPaintEvent *);
    int checkForFilters(QString &title, QString &article);
    void initFilters();
    int checkForFontTag(QString str1);
    void gradientRect(int x, int y, int width, int height);
    bool mouseInGrip(QPoint mousePos);
    void refreshFeed();
    void mouseButtonPressed(QPoint p , QObject *o);
    void mouseDblClicked(QMouseEvent * mouseEvent);
    void mouseMove(QPoint p, QMouseEvent *e, QObject *o);
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // VIEWWINDOW_H

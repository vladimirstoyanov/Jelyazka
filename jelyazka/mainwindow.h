/*
    mainwindow.h
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <qsizegrip.h>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QEvent>
#include <QLabel>
#include <QList>
#include <QPainter>
#include <QResizeEvent>
#include <QShowEvent>
#include <QStringList>
#include <QStyle>
#include <QWidget>

#include "data.h"
#include "database.h"
#include "help.h"
#include "http.h"
#include "Options/optionswindow.h"
//#include "rssthread.h"
//#include "rsssearchgui.h"
#include "search.h"
#include "ui_mainwindow.h"

namespace Ui
{
    class MainWindow;
}

class RSSSearchGUI;
class OptionsWindow;

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    QList<QString> filters_qlist; //ToDo: move it to the private section

    explicit MainWindow(
            QWidget *parent = 0);
    virtual ~MainWindow();

    void initDataInComboBoxFromStructure();
    //void initTextBrowser();
    //void onUpdate(QList<bool> l_removed_items);

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void onUpdateRSSData ();
private slots:
    //ToDo: rename the below functions
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *);

private:
    bool eventFilter(QObject *, QEvent *);

private:
    void addToCombobox(const QString &str);
    void gradientRect(const int x, const int y, const int width, const int height);
    //void initDataInComboBox();
    //void initFilters();
    void mouseButtonPressed(QPoint p , QObject *o);
    void mouseDblClicked(QMouseEvent * mouseEvent);
    void mouseMove(QPoint p, QMouseEvent *e, QObject *o);
    //void refreshFeed();

private:
    bool mouseInGrip(QPoint mousePos);
    //int checkForFilters(QString &title, QString &article);
    //int showArticle(int struct_index, int article_index);
    //int checkForFontTag(const QString &str1);

private:
    ulong current_site_index_;
    ulong current_article_index_;
    std::shared_ptr<Ui::MainWindow> ui_;
    //std::shared_ptr<RSSThread> rss_thread_;
    std::shared_ptr<QLabel> image_add_rss_label_;
    QImage add_rss_button_image_;
    std::shared_ptr<QLabel> image_options_label_;
    QImage options_button_image_;
    std::shared_ptr<QLabel> image_refresh_label_;
    QImage refresh_button_image_;
    std::shared_ptr<QLabel> image_help_label_;
    QImage help_button_image_;
    std::shared_ptr<QLabel> image_X_label_;
    QImage x_button_image_;
    std::shared_ptr<QLabel> image_minimize_label_;
    QImage minimize_button_image_;
    std::shared_ptr<QLabel> image_maximize_label_;
    QImage maximize_button_image_;
    QRect old_size_;
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
    std::map<QString, RSSData> rss_data_;

signals:
    void stateChanged(const QString &);
};

#endif // MainWindow_H

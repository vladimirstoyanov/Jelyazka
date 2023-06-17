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
#include <QScreen>
#include <QShowEvent>
#include <QStringList>
#include <QStyle>
#include <QWidget>


#include "database.h"
#include "RSS/rss_data.h"
#include "RSS/article_manager.h"

#include "ui_mainwindow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    QList<QString> filters_qlist; //ToDo: move it to the private section

    explicit MainWindow(
            QWidget *parent = 0);
    virtual ~MainWindow();

    void initDataInComboBoxFromStructure(); //ToDo: move this method in the private section

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void onRssDataUpdated (const std::vector<RSSData> &updated_rss_data);
    void onUpdateRSSData  ();

private slots:
    void on_previousButton_clicked(); // button '<'
    void on_nextButton_clicked(); // button '>'
    void on_titleComboBox_currentIndexChanged(const QString &); //a combobox with rss titles

private:
    void addToCombobox(const QString &str);
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *, QEvent *);
    void gradientRect(const int x, const int y, const int width, const int height);
    void mouseButtonPressed(QPoint p , QObject *o);
    void mouseDblClicked(QMouseEvent * mouseEvent);
    bool mouseInGrip(QPoint mousePos);
    void mouseMove(QPoint p, QMouseEvent *e, QObject *o);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
    void setupGui ();
    void setHtmlContent (const RSSArticle rss_article);
    void showArticle();
    void showEvent(QShowEvent *);
    void showNextArticle();
    void showPreviousArticle ();

    ArticleManager                  article_manager_;
    QImage                          add_rss_button_image_;
    QPoint                          current_point_;
    ulong                           current_article_index_;
    ulong                           current_site_index_;
    DataBase                        data_base;
    QImage                          help_button_image_;
    int                             height_;
    std::shared_ptr<QLabel>         image_add_rss_label_;
    std::shared_ptr<QLabel>         image_help_label_;
    std::shared_ptr<QLabel>         image_maximize_label_;
    std::shared_ptr<QLabel>         image_minimize_label_;
    std::shared_ptr<QLabel>         image_options_label_;
    std::shared_ptr<QLabel>         image_refresh_label_;
    std::shared_ptr<QLabel>         image_X_label_;
    bool                            is_close_;
    bool                            is_flag_maximized_;
    bool                            is_minimize_;
    bool                            is_minimize_changed_;
    bool                            is_maximize_changed_;
    bool                            is_press_released_;
    bool                            is_resizing_;
    bool                            is_show_flag_;
    bool                            is_X_changed_;
    QImage                          maximize_button_image_;
    QImage                          minimize_button_image_;
    QPoint                          move_point_pos_;
    QRect                           old_size_;
    QImage                          options_button_image_;
    QImage                          refresh_button_image_;
    QPoint                          resize_point_;
    std::map<QString, RSSData>      rss_data_;
    std::shared_ptr<Ui::MainWindow> ui_;
    int                             width_;
    QImage                          x_button_image_;

signals:
    void stateChanged(const QString &);
};

#endif // MainWindow_H

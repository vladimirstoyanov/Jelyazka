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
#include "sitestruct.h"
#include "search.h"
#include "net.h"
#include <QMouseEvent>
#include <QEvent>
#include "web_search_interface.h"
#include <QPainter>
#include "optionswindow.h"
#include <qsizegrip.h>
#include <QStringList>
#include <QList>
#include "help.h"
#include "db.h"

namespace Ui {
class ViewWindow;
}

class WebSearchInterface;
class OptionsWindow;

class ViewWindow : public QWidget
{
    Q_OBJECT
    
public:
    QList<QString> l_filters;

    explicit ViewWindow(QWidget *parent = 0, SiteStruct *tmp_site_struct=NULL);
    ~ViewWindow();

    void initDataInComboBoxFromStructure();
    void initTextBrowser();
    void onUpdate(QList<bool> l_removed_items);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    ulong current_site_index;
    ulong current_article_index;
    Ui::ViewWindow *ui;
    SiteStruct *site_struct;
    QLabel *imageAddRSSLabel;
    QImage add_rss_button_img;
    QLabel *imageOptionsLabel;
    QImage options_button_img;
    QLabel *imageRefreshLabel;
    QImage refresh_button_img;
    QLabel *imageHelpLabel;
    QImage help_button_img;
    QLabel *imageXLabel;
    QImage x_button_img;
    QLabel *imageMinimizeLabel;
    QImage minimize_button_img;
    QLabel *imageMaximizeLabel;
    QImage maximize_button_img;
    WebSearchInterface *wsi;
    OptionsWindow *ow;
    //QSizeGrip *size_grip;
    QRect old_size;
    Help *help_gui;
    bool show_flag;
    bool resizing;
    bool minimize;
    bool close;
    DB db;


    int width;
    int height;
    bool isXchanged;
    bool isMinimizechanged;
    bool isMaximizechanged;
    bool flagMaximized;
    bool pressReleased;
    QPoint curPoint;
    QPoint movePointPos;
    QPoint resizePoint;
    struct article
    {
        QString title;
        QString link;
        QString text;
        article()
        {
            title="";
            link="";
            text ="";
        }
    };
    std::vector <article> site_view_structure;

    void initDataInComboBox();
    void addToCombobox(QString str);
    int showArticle(uint struct_index, uint article_index);
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

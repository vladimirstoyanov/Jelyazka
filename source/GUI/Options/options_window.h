/*
    optionswindow.h
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
#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <QMessageBox>
#include <QResizeEvent>
#include <QWidget>

#include "database.h"
#include "feeds_options.h"
#include "filters_options.h"
#include "notifications_options.h"
#include "options.h"
#include "proxy_options.h"

#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class MainWindow;

class OptionsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsWindow(
            QWidget *parent = nullptr);

    virtual ~OptionsWindow();

private:
    DataBase                                data_base_;
    std::shared_ptr<QLabel>                 download_feed_status_;
    QList<bool>                             l_items_for_remove_;
    const unsigned int                      offset_between_widgets_;
    std::vector<std::shared_ptr<IOptions>>  options;
    std::shared_ptr<Ui::OptionsWindow>      ui_;

    void addItemToTreeView(const QString &name);
    int addToFeedList(const QString &str);
    int cf_label_search_width(); //ToDo: change the function name
    void closeEvent (QCloseEvent *);
    void createOptions ();
    void insertRowToRSSTable(const QString &site_name, const QString &url, const QString &version);
    void loadSettings();
    void resizeEvent(QResizeEvent *event);
    void returnModifedString(QString &str);
    void saveSettings();
    void setupGui ();
    void showEvent(QShowEvent *);
    void treeWidgetSetup ();
    void widgetsSetup ();

private slots:
    void on_okButton_clicked(); //'OK' button clicked
    void on_cancelButton_clicked(); //'Cancel' button clicked
    void on_treeWidget_clicked(const QModelIndex &index);

signals:
    void stateChanged   (const QString &);

};
#endif // OPTIONSWINDOW_H

/*
    rsssearchgui.h
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
#ifndef WEB_SEARCH_INTERFACE_H
#define WEB_SEARCH_INTERFACE_H

#include <limits.h>
#include <map>
#include <memory>
#include <vector>

#include <QApplication>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QFontMetrics>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMutex>
#include <QWidget>
#include <QResizeEvent>
#include <QSize>
#include <QStandardItemModel>
#include <QString>
#include <QtCore>
#include <QTableView>
#include <QTextCodec>
#include <QThreadPool>

#include "http.h"
#include "logger.h"
#include "RSS/parserss.h"
#include "rsssearchthread.h"
#include "search.h"
#include "ui_rsssearchgui.h"

namespace Ui
{
    class RSSSearchGUI;
}

class RSSSearchGUI : public QWidget
{
    Q_OBJECT

public:
    explicit RSSSearchGUI(QWidget *parent = nullptr);
    virtual ~RSSSearchGUI();

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);

private:
    void closeEvent(QCloseEvent *);

private:
    //ToDo: replace tree with std::map
    /*
    struct TreeNode {
       QString item_;
       TreeNode *left_;
       TreeNode *right_;
       TreeNode(QString str = "") {
          item_ = str;
          left_ = NULL;
          right_ = NULL;
       }
    };
    */
    //typedef TreeNode treenode;
    std::map <QString, RSSData> rss_data_;

private:
    //void buidBinaryTreeFromDBData();
    QString changeName(const QString &name); //ToDo: rename this function
    int checkExistingURL(const QString &url);
    int checkForExistingURL(const QString &url);
    void clearSearchCache();
    void convertBigEndianToLittleEndian(QString &url);
    //int countNodes(TreeNode *node);
    //void deleteKey(QString key, TreeNode **T);
    //void destroyTree(TreeNode *leaf);
    //bool editNode(TreeNode *root, QString item, QString new_item);
    //treenode* findMin(TreeNode *T);
    QString getEncodingFromRSS(const QString &content);
    QString insertName(const QString &name);
    void interateSite(QString url_addres/*, vector<QString>&result_urls*/);
    int isFeedChecked(const QString &url, int &index);
    void paintRows();
    void returnModifedString(QString &str);
    RSSSearchGUIThread *rss_search_thread_;
    //void treeInsert(TreeNode *&root, QString newItem);
    //bool treeContains( TreeNode *root, QString item );

private:
    DataBase data_base_;
    std::vector<std::shared_ptr<RSSData>> feeds_struct_tmp_;
    std::shared_ptr<QGridLayout> grid_;
    bool is_user_edit_;
    bool is_program_edit_;
    std::shared_ptr<QStandardItemModel> model_;
    std::vector<QString> old_names_;
    std::shared_ptr<ParseRSS> parse_rss_;
    std::shared_ptr<QThreadPool> thread_pool_;
    std::shared_ptr<QThreadPool> thread_pool_2;
    std::shared_ptr<Ui::RSSSearchGUI> ui_;

private slots:
    //ToDo: rename the below functions
    void on_modelItemChanged(QStandardItem*);
    void on_pushButton_clicked(); //'Search' button
    void on_pushButton_3_clicked(); //'Remove' button clicked
    void on_pushButton_2_clicked(); //"add RSS feeds" button

public slots:
    void onEndOfUrls();
    void onFoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version);

signals:
    void stateChanged (const QString &);
};

#endif // WEB_SEARCH_INTERFACE_H

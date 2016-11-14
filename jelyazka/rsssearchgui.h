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

#include <QtCore>
#include <QMutex>
#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <vector>
#include <QString>
#include <QGridLayout>
#include <QFontMetrics>
#include <QTextCodec>
#include <QSize>
#include <QCloseEvent>
#include <QThreadPool>
#include "logger.h"
#include "rsssearchthread.h"
#include "rssthread.h"
#include "mainwindow.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "data.h"
#include "parserss.h"
#include <limits.h>

namespace Ui {
class RSSSearchGUI;
}

class MainWindow;

class RSSSearchGUI : public QWidget
{
    Q_OBJECT

public:
    explicit RSSSearchGUI(QWidget *parent = 0, RSSThread *rss_thread=NULL, MainWindow *main_window=NULL, Data *data = NULL);
    ~RSSSearchGUI();
    RSSSearchGUIThread *mThread;

public slots:
    //void onAddRss(QString name, bool finish);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_modelItemChanged(QStandardItem*);

public slots:
    void onFoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version);
    void onEndOfUrls();

private:
    Ui::RSSSearchGUI *ui_;
    QStandardItemModel *model_;
    QGridLayout *grid_;
    RSSThread *rss_thread_;
    MainWindow *main_window_;
    QThreadPool *thread_pool_;
    QThreadPool *thread_pool_2;
    bool is_user_edit_;
    bool is_program_edit_;
    DataBase data_base_;
    Data *data_;
    ParseRSS *parse_rss_;

    //ToDo: replace tree with std::map
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
    TreeNode *tree_node_;
    typedef TreeNode treenode;

    boost::ptr_list<RSSData> feeds_struct_tmp_;
    boost::ptr_vector<QString> old_names_;

    void treeInsert(TreeNode *&root, QString newItem);
    bool treeContains( TreeNode *root, QString item );
    QString change_name(QString name);
    int countNodes(TreeNode *node);
    bool editNode(TreeNode *root, QString item, QString new_item);
    void returnModifedString(QString &str);
    void interateSite(QString url_addres/*, vector<QString>&result_urls*/);
    void closeEvent(QCloseEvent *);
    void paintRows();
    int checkExistingURL(QString url);
    int checkForExistingURL(QString url);
    void convertBigEndianToLittleEndian(QString &url);
    QString getEncodingFromRSS(QString content);
    void clearSearchCache();
    int isFeedChecked(QString url, int &index);
    QString insertName(QString name);
    void buidBinaryTreeFromDBData();
    void deleteKey(QString key, TreeNode **T);
    treenode* findMin(TreeNode *T);
    void destroyTree(TreeNode *leaf);

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);
};

#endif // WEB_SEARCH_INTERFACE_H

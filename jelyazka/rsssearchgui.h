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
#include <memory>
#include <vector>

#include <QCloseEvent>
#include <QDebug>
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

#include "data.h"
#include "http.h"
#include "logger.h"
#include "mainwindow.h"
#include "RSS/parserss.h"
#include "rsssearchthread.h"
#include "rssthread.h"
#include "search.h"
#include "ui_rsssearchgui.h"

namespace Ui {
class RSSSearchGUI;
}

class MainWindow;

class RSSSearchGUI : public QWidget
{
    Q_OBJECT

public:
    explicit RSSSearchGUI(QWidget *parent = 0, std::shared_ptr<RSSThread> rss_thread=nullptr, MainWindow *main_window=nullptr, std::shared_ptr<Data> data = nullptr);
    virtual ~RSSSearchGUI();
    RSSSearchGUIThread *mThread;

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *);

private:
    void closeEvent(QCloseEvent *);

private:
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
    typedef TreeNode treenode;

private:
    void buidBinaryTreeFromDBData();
    void clearSearchCache();
    void convertBigEndianToLittleEndian(QString &url);
    void deleteKey(QString key, TreeNode **T);
    void destroyTree(TreeNode *leaf);
    void interateSite(QString url_addres/*, vector<QString>&result_urls*/);
    void paintRows();
    void returnModifedString(QString &str);
    void treeInsert(TreeNode *&root, QString newItem);
    bool treeContains( TreeNode *root, QString item );

private:
    bool editNode(TreeNode *root, QString item, QString new_item);
    int checkExistingURL(QString url);
    int checkForExistingURL(QString url);
    int countNodes(TreeNode *node);
    int isFeedChecked(QString url, int &index);
    treenode* findMin(TreeNode *T);
    QString change_name(QString name); //ToDo: rename this function
    QString getEncodingFromRSS(QString content);
    QString insertName(QString name);

private:
    std::shared_ptr<Ui::RSSSearchGUI> ui_;
    std::shared_ptr<QStandardItemModel> model_;
    std::shared_ptr<QGridLayout> grid_;
    std::shared_ptr<RSSThread> rss_thread_;
    std::shared_ptr<MainWindow> main_window_;
    std::shared_ptr<QThreadPool> thread_pool_;
    std::shared_ptr<QThreadPool> thread_pool_2;
    bool is_user_edit_;
    bool is_program_edit_;
    DataBase data_base_;
    std::shared_ptr<Data> data_;
    std::shared_ptr<ParseRSS> parse_rss_;
    TreeNode *tree_node_;
    std::vector<std::shared_ptr<RSSData>> feeds_struct_tmp_;
    std::vector<QString> old_names_;

private slots:
    //ToDo: rename the below functions
    void on_modelItemChanged(QStandardItem*);
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

public slots:
    void onFoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version);
    void onEndOfUrls();

signals:
    void stateChanged (const QString &);
};

#endif // WEB_SEARCH_INTERFACE_H

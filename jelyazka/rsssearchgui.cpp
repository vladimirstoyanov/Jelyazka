/*
    web_search_interface.cpp
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
    along with this program.  If not, see <htthread_pool://www.gnu.org/licenses/>.
*/
#include "rsssearchgui.h"
#include "ui_rsssearchgui.h"
#include "http.h"
#include "search.h"
#include <QDebug>

RSSSearchGUI::RSSSearchGUI(QWidget *parent, RSSThread *rss_thread, ViewWindow *view_window, Data *data) :
    QWidget(parent),
    ui_(new Ui::RSSSearchGUI)
{
    ui_->setupUi(this);
    data_ = data;
    parse_rss_ = new ParseRSS(data_);

    this->setMinimumHeight(200);
    this->setMinimumWidth(350);

    rss_thread_ = rss_thread;

    thread_pool_ = new QThreadPool(this);
    thread_pool_->setMaxThreadCount(5);


    thread_pool_2 = new QThreadPool(this);
    thread_pool_2->setMaxThreadCount(10);

    view_window_ = view_window;

    //init gryd layout
    grid_ = new QGridLayout;
    grid_->addWidget(ui_->lineEdit,0,0);
    grid_->addWidget(ui_->pushButton,0,1);
    grid_->addWidget(ui_->tableView,1,0);
    grid_->addWidget(ui_->pushButton_2,3,0);
    grid_->addWidget(ui_->pushButton_3,1,1);
    grid_->addWidget(ui_->label,2,0);
    this->setLayout(grid_);

    //init QStandardItemModel and set it to ui->tableView (QTableView var)
    model_ = new QStandardItemModel(0,3,this);
    model_->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model_->setHorizontalHeaderItem(1, new QStandardItem(QString("URL")));
    model_->setHorizontalHeaderItem(2, new QStandardItem(QString("Encoding")));

    model_->setHorizontalHeaderItem(3, new QStandardItem(QString("Add to list")));
    ui_->tableView->setModel(model_);

    //start thread
    mThread = new RSSSearchGUIThread();
    mThread->setAutoDelete(false);
    connect(mThread, SIGNAL(FoundRSS(int,QString, QString, QString, QString,int)), this, SLOT(onFoundRSS(int,QString,QString,QString, QString,int)),Qt::QueuedConnection);
    connect(mThread, SIGNAL(EndOfUrls()),this, SLOT(onEndOfUrls()));

    //init ui->tableView item changed event
    connect(model_, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(on_modelItemChanged(QStandardItem*)));

    ui_->label->setText("");
    user_edit_ = true;
    program_edit_ = false;
}

RSSSearchGUI::~RSSSearchGUI()
{
    delete ui_;
    delete model_;
    delete grid_;
    thread_pool_2->waitForDone();
    mThread->deleteLater();
    delete thread_pool_;
    delete thread_pool_2;

    if (tree_node_!=NULL)
    {
        destroyTree(tree_node_);
        tree_node_=NULL;
    }


    if (feeds_struct_tmp_.size()>0)
        feeds_struct_tmp_.clear();
    old_names_.clear();
}

void RSSSearchGUI::closeEvent(QCloseEvent * event)
{
    if (ui_->pushButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        mThread->stop_thread = true;
        thread_pool_2->waitForDone();
		#ifdef _WIN32
            thread_pool_2->clear();
		#endif
        thread_pool_2->releaseThread();
        clearSearchCache();
        ui_->pushButton->setText("Search");
        ui_->label->setText("");
        QApplication::restoreOverrideCursor();
    }
    this->hide();
    event->ignore();

    if (tree_node_!=NULL)
    {
        destroyTree(tree_node_);
        tree_node_ = NULL;
    }

    if (feeds_struct_tmp_.size()>0)
        feeds_struct_tmp_.clear();
    old_names_.clear();
}

//paint rows in ui->tableView
void RSSSearchGUI::paintRows()
{
    for(int i = 0; i<model_->rowCount(); ++i)
    {
        if (i%2 == 0)
        {
            for(int j = 0; j<model_->columnCount(); ++j)
                model_->item(i,j)->setBackground(QBrush(QColor(255,255,255)));
            continue;
        }
        for(int j = 0; j<model_->columnCount(); ++j)
            model_->item(i,j)->setBackground(QBrush(QColor(200,249,253)));
    }
}

//check for existing url in tableView second column data
int RSSSearchGUI::checkExistingURL(QString url)
{
    QString itemText = "";
    for(int i = 0; i<model_->rowCount(); ++i)
    {
       itemText =  model_->item(i,1)->text();
        if (url == itemText)
            return 1;
    }
    return 0;
}

int RSSSearchGUI::checkForExistingURL(QString url)
{
    if (rss_thread_ == NULL)
        return 1;

    for (uint i=0; i<data_->size(); i++)
        if (url == data_->at(i)->getURL())
            return 1;

    return 0;

}

void RSSSearchGUI::convertBigEndianToLittleEndian(QString &url)
{
    for (int i=0; i<url.length(); i++)
    {
        int digit = int(url[i].toLatin1());
        if (digit>64 && digit<91)
            url[i] = url[i].toLower();
    }

}

void RSSSearchGUI::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220) //'enter' button
    {
        ui_->pushButton->click();
    }
}

void RSSSearchGUI::showEvent(QShowEvent *)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    tree_node_ = new TreeNode;
    int row_count = model_->rowCount();
    model_->removeRows(0, row_count);
    ui_->lineEdit->setText("");
    ui_->label->setText("");
}

void RSSSearchGUI::clearSearchCache ()
{
    mThread->l_url.clear();
    mThread->l_flags.clear();
    mThread->l_url2.clear();
    mThread->deleteAllFrom_all_url_table();
}

void RSSSearchGUI::onEndOfUrls()
{
    thread_pool_2->waitForDone();
	
    #ifdef _WIN32
            thread_pool_2->clear();
		#endif
    thread_pool_2->releaseThread();
    mThread->l_flags.clear();

    if (mThread->l_url2.size() == 0) //end of searching
    {
        ui_->pushButton->setText("Search");
        QString text = ui_->label->text();
        if (text!="Fail to connect!")
           ui_->label->setText("");
    }

    if (mThread->l_url.size()>0)
           qDebug()<<"Logical error: in RSSSearchGUI::onEndOfUrls() if (mThread->l_url.size()>0)";

    boost::ptr_list<QString>::iterator l_url2_itr;
    for (l_url2_itr = mThread->l_url2.begin(); l_url2_itr!=mThread->l_url2.end(); l_url2_itr++)
    {
        QString *tmp = new QString (*l_url2_itr);
        mThread->l_url.push_back(tmp);
        mThread->l_flags.push_back(0);
    }

    mThread->l_url2.clear();
    qDebug()<<"Size: " + QString::number(mThread->l_url.size());
    for (int i=0; i<mThread->l_flags.size(); i++)
        thread_pool_2->start(mThread);
}

//'Search' button
void RSSSearchGUI::on_pushButton_clicked()
{
    if (ui_->pushButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        mThread->stop_thread = true;
        thread_pool_2->waitForDone();
        ui_->pushButton->setText("Search");
        ui_->label->setText("");
        clearSearchCache();
        #ifdef _WIN32
            thread_pool_2->clear();
		#endif
        thread_pool_2->releaseThread();
        QApplication::restoreOverrideCursor();
    }
    else if (ui_->pushButton->text() == "Search")
    {
        mThread->stop_thread = false; //if this flag is true, the threads stops
        ui_->pushButton->setText("Stop Searching");
        QString *url = new QString(ui_->lineEdit->text());
        convertBigEndianToLittleEndian(*url);
        clearSearchCache();
        mThread->l_url.push_back(url);
        mThread->insertUrlDB(*url);
        mThread->l_flags.push_back(0);
        if (!mThread->setUrlRoot(*url))
        {
            QMessageBox::critical(0,"Error","Invalid URL!");
            return;
        }
        #ifdef _WIN32
            thread_pool_2->clear();
		#endif
        thread_pool_2->releaseThread();
        thread_pool_2->start(mThread);
    }
}

void RSSSearchGUI::onFoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version) //event function, when found rss
{
    if (type == 0 || type == -1)
    {

        if (checkExistingURL(url))
            return;
        user_edit_ = false;
        parse_rss_->convert_string(name, false);
        while(treeContains(tree_node_,name))
            name = change_name(name); //make unique name
        treeInsert(tree_node_, name);

        if (INT_MAX<=old_names_.size())
            return;

        old_names_.push_back(new QString(name));

        RSSData *rd = new RSSData();
        rd->setSiteName(name);
        rd->setURL(url);


        if (!version)
        {
            rd->setVersion(0);
            rd->setEncoding(encoding);
            parse_rss_->getArticlesFromRSSContent(web_source, rd);
        }
        else
        {
            rd->setVersion("2005");
            parse_rss_->getArticlesFromRDFContent(web_source, rd);
        }

        feeds_struct_tmp_.push_back(rd);

        int row_count = model_->rowCount();
        model_->setRowCount(row_count+1);
        model_->setData(model_->index(row_count,0),name);
        model_->setData(model_->index(row_count,1),url);
        model_->setData(model_->index(row_count,2),encoding);

        QStandardItem* item0 = new QStandardItem(true);
        item0->setCheckable(true);
        item0->setCheckState(Qt::Checked);

        item0->setEditable(false);
        model_->setItem(row_count, 3, item0);

        model_->item(model_->rowCount()-1,1)->setEditable(false);
        model_->item(model_->rowCount()-1,2)->setEditable(false);
        model_->item(model_->rowCount()-1,3)->setEditable(false);

        paintRows();

        ui_->tableView->scrollToBottom();
        ui_->tableView->resizeColumnToContents(0);
        user_edit_ = true;

    }
    if (type == 1)
    {
        returnModifedString(url);
        ui_->label->setText(url);
    }
}

//change string of label to be within a window size
void RSSSearchGUI::returnModifedString(QString &str)
{
    QRect rect;
    QFontMetrics fm(ui_->label->font());
    QString str_tmp = str, add_str="";
    int pixel_width = 0, dots_width=0, window_width = 0;
    QSize window_size = this->size();
    window_width = window_size.width()-120;

    rect = fm.boundingRect("...");
    dots_width = rect.width();
    rect = fm.boundingRect(str_tmp);
    pixel_width=rect.width();
    if (pixel_width>=window_width)
    {
        add_str+="...";
    }
    while (pixel_width >= window_width)
    {
        str_tmp = str_tmp.left(str_tmp.size()-1);
        rect = fm.boundingRect(str_tmp);
        pixel_width=rect.width() + dots_width;
    }
    str = str_tmp + add_str;
}

void RSSSearchGUI::on_pushButton_3_clicked() //'Remove' button clicked
{
    QModelIndexList indexes = ui_->tableView->selectionModel()->selectedRows();
    qSort(indexes.begin(), indexes.end());
    while (!indexes.isEmpty())
    {
        model_->removeRows(indexes.last().row(), 1);
        deleteKey(old_names_[indexes.last().row()],&tree_node_);
        old_names_.erase(old_names_.begin() + indexes.last().row());

        indexes.removeLast();
    }
    paintRows();
}

void RSSSearchGUI::on_pushButton_2_clicked() //add RSS feeds button
{
    this->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (feeds_struct_tmp_.size()>0)
        buidBinaryTreeFromDBData();

    boost::ptr_list<RSSData>::iterator feeds_struct_tmp_iterator;
    for(feeds_struct_tmp_iterator = feeds_struct_tmp_.begin(); feeds_struct_tmp_iterator!=feeds_struct_tmp_.end(); ++feeds_struct_tmp_iterator)
    {
        int row=0;
        if (!isFeedChecked(feeds_struct_tmp_iterator->getURL(), row)) //if rss feed is unchecked
            continue;

        QModelIndex mi;
        QVariant v;

        mi = model_->index(row,0);
        v=mi.data();
        QString name_tmp = insertName(v.toString());
        feeds_struct_tmp_iterator->setSiteName(name_tmp);

        QString version = feeds_struct_tmp_iterator->getVersion();
        data_base_.insertIntoCollectFeeds(feeds_struct_tmp_iterator->getSiteName(), feeds_struct_tmp_iterator->getURL(),version);
        data_base_.insertIntoFavoriteFeeds(feeds_struct_tmp_iterator->getSiteName(), feeds_struct_tmp_iterator->getURL(), version);

        if (INT_MAX<=data_->size()) //prevent int overflow
        {
            QMessageBox::critical(0,"Error","Size of RSS feeds must be less than from " + QString::number(INT_MAX) + "! Please remove any RSS feeds!");
            break;
        }

        //add to 'rss_thread_'
        data_->pushBack(rss_thread_->initStruct(feeds_struct_tmp_iterator->getSiteName(),"RSS",feeds_struct_tmp_iterator->getURL()));
        data_->at(data_->size()-1)->setVersion(version);

        //adding data_ (titles, links, descriptions)
        RSSArticle art;
        for (int i=0; i<feeds_struct_tmp_iterator->getArticlesSize(); i++)
        {
            art.setTitle(feeds_struct_tmp_iterator->articleAt(i).getTitle());
            art.setLink(feeds_struct_tmp_iterator->articleAt(i).getLink());
            art.setText(feeds_struct_tmp_iterator->articleAt(i).getText());
            art.setDate(feeds_struct_tmp_iterator->articleAt(i).getDate());

            data_->at(data_->size()-1)->articlesPushBack(art);
        }
    }
    //There is no data in rss_thread_ without below row in ViewWindow
    rss_thread_->setAutoDelete(true);

    view_window_->initDataInComboBoxFromStructure();
    view_window_->initTextBrowser();

    QApplication::restoreOverrideCursor();

    if (feeds_struct_tmp_.size()>0)
        feeds_struct_tmp_.clear();

    if (tree_node_!=NULL)
    {
        destroyTree(tree_node_);
        tree_node_ = NULL;
    }
    this->setEnabled(true);
    this->close();
}


int RSSSearchGUI::isFeedChecked(QString url, int &index)
{
    for(int i = 0; i<model_->rowCount(); ++i)
    {
        //check for existing url
        if (model_->item(i,1)->text() == url )
        {
            index = i;
            QModelIndex index= ui_->tableView->model()->index(i,3, QModelIndex());
            if(index.data(Qt::CheckStateRole) == Qt::Checked)
                return 1;
            return 0;
        }
    }
    return 0;
}

void RSSSearchGUI::treeInsert(TreeNode *&root, QString newItem) {
   if ( root == NULL ) {
      root = new TreeNode( newItem );
      return;
   }
   else if ( newItem < root->item_ ) {
      treeInsert( root->left_, newItem );
   }
   else {
      treeInsert( root->right_, newItem );
   }
}

bool RSSSearchGUI::treeContains( TreeNode *root, QString item ) {
   if ( root == NULL ) {
      return false;
   }
   else if ( item == root->item_ ) {
      return true;
   }
   else if ( item < root->item_ ) {
      return treeContains( root->left_, item );
   }
   else {
      return treeContains( root->right_, item );
   }
}


int RSSSearchGUI::countNodes(TreeNode *node) {
   if ( node == NULL ) {
      return 0;
   }
   else {
      int leftCount = countNodes( node->left_ );
      int rightCount = countNodes( node->right_ );
      return  1 + leftCount + rightCount;
   }
}
bool RSSSearchGUI::editNode(TreeNode *root, QString item, QString new_item)
{
   if ( root == NULL ) {
      return false;
   }
   else if ( item == root->item_ ) {
      root->item_ = new_item;
      return true;
   }
   else if ( item < root->item_ ) {
      return editNode( root->left_, item, new_item );
   }
   else {
      return editNode( root->right_, item, new_item );
   }
}
QString RSSSearchGUI::change_name(QString name)
{
    if (name.length()<1)
    {
        name+="1";
        return name;
    }

    int n =  name[name.length()-1].unicode();
    //qDebug()<<names[index];
    if (n<48 || n>57)
    {
        name+="1";
        return name;
    }

    int number = 0;
    int multiple = 1;
    int num_len = 0;
    for (int i=name.length()-1; i>=0; i--)
    {
        int num = name[i].unicode();
        if (num>47 && num<58)
        {
            num_len++;
            number= (num-'0')*multiple + number;
            multiple*=10;
            continue;
        }
        break;
    }

    //qDebug()<<names[index];
    number+=1;
    QString num_str = QString::number(number);

    if (num_len<num_str.length())
        name+="0";

    int j=name.length()-1;
    for (int i = num_str.length()-1; i>=0; i--)
    {
        name[j--] = num_str[i];
    }

    return name;
}

void RSSSearchGUI::on_modelItemChanged(QStandardItem*item)
{
    bool in_if=false;
    if (item->column() == 0 && user_edit_ && !program_edit_)
    {
        //check name and make unique
        QString name  = item->text();

        while(treeContains(tree_node_,name))
            name = change_name(name); //make unique name

        editNode(tree_node_, old_names_[item->row()],name);
        old_names_[item->row()] = name;

        if (name != item->text())
        {
            program_edit_ = true;
            in_if = true;
            model_->setData(model_->index(item->row(),0),name); //set new name
        }
    }
    if (program_edit_ && !in_if)
        program_edit_ = false;
}
QString RSSSearchGUI::insertName(QString name)
{
    while(treeContains(tree_node_,name))
        name = change_name(name); //make unique name

    //edit name
    treeInsert(tree_node_, name);
    return name;
}

void RSSSearchGUI::buidBinaryTreeFromDBData()
{
    if (tree_node_!=NULL)
    {
        destroyTree(tree_node_);
        tree_node_ = NULL;
    }
    tree_node_ = new TreeNode;

    boost::ptr_vector<QString> tmp;
    boost::ptr_vector<QString>::iterator it;
    data_base_.getCollectFeeds(&tmp);

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        while(treeContains(tree_node_,*it))
            *it = change_name(*it); //make unique name
        treeInsert(tree_node_, *it);
    }
}

RSSSearchGUI::treenode* RSSSearchGUI::findMin(TreeNode *T)
{
    while (NULL != T->left_)
        T = T->left_;
    return T;
}

void RSSSearchGUI::deleteKey(QString key, TreeNode **T)
{
    if (NULL == *T) {
        return;
    }
    else {
        if (key < (*T)->item_)
          deleteKey(key, &(*T)->left_);
        else if (key > (*T)->item_)
          deleteKey(key, &(*T)->right_);
        else
        if ((*T)->left_ && (*T)->right_) {
          struct TreeNode *replace = findMin((*T)->right_);
          (*T)->item_ = replace->item_;
          deleteKey((*T)->item_, &(*T)->right_);
        }
        else {
          struct TreeNode *temp = *T;
          if ((*T)->left_)
            *T = (*T)->left_;
          else
            *T = (*T)->right_;
          delete temp;
        }
    }
}

void RSSSearchGUI::destroyTree(TreeNode *leaf)
{
  if(leaf!=NULL)
  {
    destroyTree(leaf->left_);
    destroyTree(leaf->right_);
    delete leaf;
  }
}
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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "web_search.h"
#include "ui_web_search_interface.h"
#include "http.h"
#include "search.h"
#include <QDebug>

WebSearchInterface::WebSearchInterface(QWidget *parent, SiteStruct *tmp_site_struct, ViewWindow *view_window, Data *data_tmp) :
    QWidget(parent),
    ui(new Ui::WebSearchInterface)
{
    ui->setupUi(this);
    data = data_tmp;
    parseRSS = new ParseRSS(data);

    this->setMinimumHeight(200);
    this->setMinimumWidth(350);

    site_struct = tmp_site_struct;

    tp = new QThreadPool(this);
    tp->setMaxThreadCount(5);


    tp2 = new QThreadPool(this);
    tp2->setMaxThreadCount(10);

    vw = view_window;

    //init gryd layout
    grid = new QGridLayout;
    grid->addWidget(ui->lineEdit,0,0);
    grid->addWidget(ui->pushButton,0,1);
    grid->addWidget(ui->tableView,1,0);
    grid->addWidget(ui->pushButton_2,3,0);
    grid->addWidget(ui->pushButton_3,1,1);
    grid->addWidget(ui->label,2,0);
    this->setLayout(grid);

    //init QStandardItemModel and set it to ui->tableView (QTableView var)
    model = new QStandardItemModel(0,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("URL")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Encoding")));

    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Add to list")));
    ui->tableView->setModel(model);

    //start thread
    mThread = new WebSearchInterfaceThread();
    mThread->setAutoDelete(false);
    connect(mThread, SIGNAL(FoundRSS(int,QString, QString, QString, QString,int)), this, SLOT(onFoundRSS(int,QString,QString,QString, QString,int)),Qt::QueuedConnection);
    connect(mThread, SIGNAL(EndOfUrls()),this, SLOT(onEndOfUrls()));

    //init ui->tableView item changed event
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(on_modelItemChanged(QStandardItem*)));

    ui->label->setText("");
    userEdit = true;
    programEdit = false;
}

WebSearchInterface::~WebSearchInterface()
{
    delete ui;
    delete model;
    delete grid;
    tp2->waitForDone();
    mThread->deleteLater();
    delete tp;
    delete tp2;

    if (tn!=NULL)
    {
        destroyTree(tn);
        tn=NULL;
    }


    if (feeds_struct_tmp.size()>0)
        feeds_struct_tmp.clear();
    old_names.clear();
}

void WebSearchInterface::closeEvent(QCloseEvent * event)
{
    if (ui->pushButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        mThread->stop_thread = true;
        tp2->waitForDone();
		#ifdef _WIN32
			tp2->clear();
		#endif
        tp2->releaseThread();
        clearSearchCache();
        ui->pushButton->setText("Search");
        ui->label->setText("");
        QApplication::restoreOverrideCursor();
    }
    this->hide();
    event->ignore();

    if (tn!=NULL)
    {
        destroyTree(tn);
        tn = NULL;
    }

    if (feeds_struct_tmp.size()>0)
        feeds_struct_tmp.clear();
    old_names.clear();
}

//paint rows in ui->tableView
void WebSearchInterface::paintRows()
{
    for(int i = 0; i<model->rowCount(); ++i)
    {
        if (i%2 == 0)
        {
            for(int j = 0; j<model->columnCount(); ++j)
                model->item(i,j)->setBackground(QBrush(QColor(255,255,255)));
            continue;
        }
        for(int j = 0; j<model->columnCount(); ++j)
            model->item(i,j)->setBackground(QBrush(QColor(200,249,253)));
    }
}

//check for existing url in tableView second column data
int WebSearchInterface::checkExistingURL(QString url)
{
    QString itemText = "";
    for(int i = 0; i<model->rowCount(); ++i)
    {
       itemText =  model->item(i,1)->text();
        if (url == itemText)
            return 1;
    }
    return 0;
}

int WebSearchInterface::checkSiteStructForExistingURL(QString url)
{
    if (site_struct == NULL)
        return 1;

    for (uint i=0; i<data->size(); i++)
        if (url == data->at(i)->getURL())
            return 1;

    return 0;

}

void WebSearchInterface::convertBigEndianToLittleEndian(QString &url)
{
    for (int i=0; i<url.length(); i++)
    {
        int digit = int(url[i].toLatin1());
        if (digit>64 && digit<91)
            url[i] = url[i].toLower();
    }

}

void WebSearchInterface::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220) //'enter' button
    {
        ui->pushButton->click();
    }
}

void WebSearchInterface::showEvent(QShowEvent *)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    tn = new TreeNode;
    int row_count = model->rowCount();
    model->removeRows(0, row_count);
    ui->lineEdit->setText("");
    ui->label->setText("");
}

void WebSearchInterface::clearSearchCache ()
{
    mThread->l_url.clear();
    mThread->l_flags.clear();
    mThread->l_url2.clear();
    mThread->deleteAllFrom_all_url_table();
}

void WebSearchInterface::onEndOfUrls()
{
    tp2->waitForDone();
	
    #ifdef _WIN32
			tp2->clear();
		#endif
    tp2->releaseThread();
    mThread->l_flags.clear();

    if (mThread->l_url2.size() == 0) //end of searching
    {
        ui->pushButton->setText("Search");
        QString text = ui->label->text();
        if (text!="Fail to connect!")
           ui->label->setText("");
    }

    if (mThread->l_url.size()>0)
           qDebug()<<"Logical error: in WebSearchInterface::onEndOfUrls() if (mThread->l_url.size()>0)";

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
        tp2->start(mThread);
}

//'Search' button
void WebSearchInterface::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        mThread->stop_thread = true;
        tp2->waitForDone();
        ui->pushButton->setText("Search");
        ui->label->setText("");
        clearSearchCache();
        #ifdef _WIN32
			tp2->clear();
		#endif
        tp2->releaseThread();
        QApplication::restoreOverrideCursor();
    }
    else if (ui->pushButton->text() == "Search")
    {
        mThread->stop_thread = false; //if this flag is true, the threads stops
        ui->pushButton->setText("Stop Searching");
        QString *url = new QString(ui->lineEdit->text());
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
			tp2->clear();
		#endif
        tp2->releaseThread();
        tp2->start(mThread);
    }
}

void WebSearchInterface::onFoundRSS(int type, QString name, QString url, QString encoding, QString web_source, int version) //event function, when found rss
{
    if (type == 0 || type == -1)
    {

        if (checkExistingURL(url))
            return;
        userEdit = false;
        parseRSS->convert_string(name, false);
        while(treeContains(tn,name))
            name = change_name(name); //make unique name
        treeInsert(tn, name);

        if (INT_MAX<=old_names.size())
            return;

        old_names.push_back(new QString(name));

        RSSData *rd = new RSSData();
        rd->setSiteName(name);
        rd->setURL(url);


        if (!version)
        {
            rd->setVersion(0);
            rd->setEncoding(encoding);
            parseRSS->getArticlesFromRSSContent(web_source, rd);
        }
        else
        {
            rd->setVersion("2005");
            parseRSS->getArticlesFromRDFContent(web_source, rd);
        }

        feeds_struct_tmp.push_back(rd);

        int row_count = model->rowCount();
        model->setRowCount(row_count+1);
        model->setData(model->index(row_count,0),name);
        model->setData(model->index(row_count,1),url);
        model->setData(model->index(row_count,2),encoding);

        QStandardItem* item0 = new QStandardItem(true);
        item0->setCheckable(true);
        item0->setCheckState(Qt::Checked);

        item0->setEditable(false);
        model->setItem(row_count, 3, item0);

        model->item(model->rowCount()-1,1)->setEditable(false);
        model->item(model->rowCount()-1,2)->setEditable(false);
        model->item(model->rowCount()-1,3)->setEditable(false);

        paintRows();

        ui->tableView->scrollToBottom();
        ui->tableView->resizeColumnToContents(0);
        userEdit = true;

    }
    if (type == 1)
    {
        returnModifedString(url);
        ui->label->setText(url);
    }
}

//change string of label to be within a window size
void WebSearchInterface::returnModifedString(QString &str)
{
    QRect rect;
    QFontMetrics fm(ui->label->font());
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

void WebSearchInterface::on_pushButton_3_clicked() //'Remove' button clicked
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    qSort(indexes.begin(), indexes.end());
    while (!indexes.isEmpty())
    {
        model->removeRows(indexes.last().row(), 1);
        deleteKey(old_names[indexes.last().row()],&tn);
        old_names.erase(old_names.begin() + indexes.last().row());

        indexes.removeLast();
    }
    paintRows();
}

void WebSearchInterface::on_pushButton_2_clicked() //add RSS feeds button
{
    this->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if (feeds_struct_tmp.size()>0)
        buidBinaryTreeFromDBData();

    boost::ptr_list<RSSData>::iterator feeds_struct_tmp_iterator;
    for(feeds_struct_tmp_iterator = feeds_struct_tmp.begin(); feeds_struct_tmp_iterator!=feeds_struct_tmp.end(); feeds_struct_tmp_iterator++)
    {
        int row=0;
        if (!isFeedChecked(feeds_struct_tmp_iterator->getURL(), row)) //if rss feed is unchecked
            continue;

        QModelIndex mi;
        QVariant v;

        mi = model->index(row,0);
        v=mi.data();
        QString name_tmp = insertName(v.toString());
        feeds_struct_tmp_iterator->setSiteName(name_tmp);

        QString version = feeds_struct_tmp_iterator->getVersion();
        db.insertIntoCollectFeeds(feeds_struct_tmp_iterator->getSiteName(), feeds_struct_tmp_iterator->getURL(),version);
        db.insertIntoFavoriteFeeds(feeds_struct_tmp_iterator->getSiteName(), feeds_struct_tmp_iterator->getURL(), version);

        if (INT_MAX<=data->size()) //prevent int overflow
        {
            QMessageBox::critical(0,"Error","Size of RSS feeds must be less than from " + QString::number(INT_MAX) + "! Please remove any RSS feeds!");
            break;
        }

        //add to 'site_struct'
        data->push_back(site_struct->initStruct(feeds_struct_tmp_iterator->getSiteName(),"RSS",feeds_struct_tmp_iterator->getURL()));
        data->at(data->size()-1)->setVersion(version);

        //adding data (titles, links, descriptions)
        RSSArticle art;
        for (int i=0; i<feeds_struct_tmp_iterator->getArticlesSize(); i++)
        {
            art.setTitle(feeds_struct_tmp_iterator->articleAt(i).getTitle());
            art.setLink(feeds_struct_tmp_iterator->articleAt(i).getLink());
            art.setText(feeds_struct_tmp_iterator->articleAt(i).getText());

            data->at(data->size()-1)->articlesPushBack(art);
        }
    }

    site_struct->setAutoDelete(true); // tova ako go nqma, vyv viewwindow klasa pokazva, che nqma danni v site_struct
    //qDebug()<<"Size add RSS: " + QString::number(site_struct->s_struct.size());
    vw->initDataInComboBoxFromStructure();
    vw->initTextBrowser();

    QApplication::restoreOverrideCursor();

    if (feeds_struct_tmp.size()>0)
        feeds_struct_tmp.clear();

    if (tn!=NULL)
    {
        destroyTree(tn);
        tn = NULL;
    }
    this->setEnabled(true);
    this->close();
}


int WebSearchInterface::isFeedChecked(QString url, int &index)
{
    for(int i = 0; i<model->rowCount(); ++i)
    {
        //check for existing url
        if (model->item(i,1)->text() == url )
        {
            index = i;
            QModelIndex index= ui->tableView->model()->index(i,3, QModelIndex());
            if(index.data(Qt::CheckStateRole) == Qt::Checked)
                return 1;
            return 0;
        }
    }
    return 0;
}

void WebSearchInterface::treeInsert(TreeNode *&root, QString newItem) {
   if ( root == NULL ) {
      root = new TreeNode( newItem );
      return;
   }
   else if ( newItem < root->item ) {
      treeInsert( root->left, newItem );
   }
   else {
      treeInsert( root->right, newItem );
   }
}

bool WebSearchInterface::treeContains( TreeNode *root, QString item ) {
   if ( root == NULL ) {
      return false;
   }
   else if ( item == root->item ) {
      return true;
   }
   else if ( item < root->item ) {
      return treeContains( root->left, item );
   }
   else {
      return treeContains( root->right, item );
   }
}


int WebSearchInterface::countNodes(TreeNode *node) {
   if ( node == NULL ) {
      return 0;
   }
   else {
      int leftCount = countNodes( node->left );
      int rightCount = countNodes( node->right );
      return  1 + leftCount + rightCount;
   }
}
bool WebSearchInterface::editNode(TreeNode *root, QString item, QString new_item)
{
   if ( root == NULL ) {
      return false;
   }
   else if ( item == root->item ) {
      root->item = new_item;
      return true;
   }
   else if ( item < root->item ) {
      return editNode( root->left, item, new_item );
   }
   else {
      return editNode( root->right, item, new_item );
   }
}
QString WebSearchInterface::change_name(QString name)
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

void WebSearchInterface::on_modelItemChanged(QStandardItem*item)
{
    bool in_if=false;
    if (item->column() == 0 && userEdit && !programEdit)
    {
        //check name and make unique
        QString name  = item->text();

        while(treeContains(tn,name))
            name = change_name(name); //make unique name

        editNode(tn, old_names[item->row()],name);
        old_names[item->row()] = name;

        if (name != item->text())
        {
            programEdit = true;
            in_if = true;
            model->setData(model->index(item->row(),0),name); //set new name
        }
    }
    if (programEdit && !in_if)
        programEdit = false;
}
QString WebSearchInterface::insertName(QString name)
{
    while(treeContains(tn,name))
        name = change_name(name); //make unique name

    //edit name
    treeInsert(tn, name);
    return name;
}

void WebSearchInterface::buidBinaryTreeFromDBData()
{
    if (tn!=NULL)
    {
        destroyTree(tn);
        tn = NULL;
    }
    tn = new TreeNode;

    boost::ptr_vector<QString> tmp;
    boost::ptr_vector<QString>::iterator it;
    db.getCollectFeeds(&tmp);

    for (it = tmp.begin(); it!=tmp.end(); ++it)
    {
        while(treeContains(tn,*it))
            *it = change_name(*it); //make unique name
        treeInsert(tn, *it);
    }
}

WebSearchInterface::treenode* WebSearchInterface::findMin(TreeNode *T)
{
    while (NULL != T->left)
        T = T->left;
    return T;
}

void WebSearchInterface::deleteKey(QString key, TreeNode **T)
{
    if (NULL == *T) {
        return;
    }
    else {
        if (key < (*T)->item)
          deleteKey(key, &(*T)->left);
        else if (key > (*T)->item)
          deleteKey(key, &(*T)->right);
        else
        if ((*T)->left && (*T)->right) {
          struct TreeNode *replace = findMin((*T)->right);
          (*T)->item = replace->item;
          deleteKey((*T)->item, &(*T)->right);
        }
        else {
          struct TreeNode *temp = *T;
          if ((*T)->left)
            *T = (*T)->left;
          else
            *T = (*T)->right;
          delete temp;
        }
    }
}

void WebSearchInterface::destroyTree(TreeNode *leaf)
{
  if(leaf!=NULL)
  {
    destroyTree(leaf->left);
    destroyTree(leaf->right);
    delete leaf;
  }
}

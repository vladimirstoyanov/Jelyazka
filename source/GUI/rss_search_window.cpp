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
#include "rss_search_window.h"

RSSSearchGUI::RSSSearchGUI(QWidget *parent) :
    QWidget             (parent)
    , data_base_        ()
    , grid_             (std::make_shared<QGridLayout> ())
    , is_user_edit_     (false)
    , is_program_edit_  (false)
    , model_            (std::make_shared<QStandardItemModel>(0,3,this))
    , parse_rss_        (std::make_shared <ParseRSS> ())
    , ui_               (std::make_shared<Ui::RSSSearchGUI> ())

{
    setupGui();
}

RSSSearchGUI::~RSSSearchGUI()
{
    rss_search_thread_->deleteLater();

    rss_data_.clear();
}

void RSSSearchGUI::closeEvent(QCloseEvent * event)
{
    if (ui_->searchButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        rss_search_thread_->stopThread();
        ui_->searchButton->setText("Search");
        ui_->label->setText("");
        QApplication::restoreOverrideCursor();
    }
    //this->hide();
    event->ignore();

    rss_data_.clear();

    emit(stateChanged("HideRssSearchWindow"));
}

//paint rows in ui->tableView
void RSSSearchGUI::paintRows()
{
    for(int i = 0; i<model_->rowCount(); ++i)
    {
        if (i%2 == 0)
        {
            for(int j = 0; j<model_->columnCount(); ++j)
            {
                model_->item(i,j)->setBackground(QBrush(QColor(255,255,255)));
                model_->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
            }
            continue;
        }
        for(int j = 0; j<model_->columnCount(); ++j)
        {
            model_->item(i,j)->setBackground(QBrush(QColor(200,249,253)));
            model_->item(i,j)->setForeground(QBrush(QColor(0,0,0)));
        }
    }
}

//check for existing url in tableView second column data
int RSSSearchGUI::checkExistingURL(const QString &url)
{
    QString itemText = "";
    for(int i = 0; i<model_->rowCount(); ++i)
    {
       itemText =  model_->item(i,1)->text();
        if (url == itemText)
        {
            return 1;
        }
    }
    return 0;
}


void RSSSearchGUI::convertBigEndianToLittleEndian(QString &url)
{
    for (int i=0; i<url.length(); i++)
    {
        int digit = int(url[i].toLatin1());
        if (digit>64 && digit<91)
        {
            url[i] = url[i].toLower();
        }
    }

}

void RSSSearchGUI::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==16777220) //'enter' button
    {
        ui_->searchButton->click();
    }
}

void RSSSearchGUI::showEvent(QShowEvent *)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    //tree_node_ = new TreeNode;
    rss_data_.clear();

    rss_search_thread_->stopThread();
    int row_count = model_->rowCount();
    model_->removeRows(0, row_count);
    ui_->lineEdit->setText("");
    ui_->label->setText("");
}

void RSSSearchGUI::onEndOfUrls()
{
     ui_->searchButton->setText("Search");
     QString text = ui_->label->text();
     if (text!="Fail to connect!")
     {
         ui_->label->setText("");
     }
}

//'Search' button
void RSSSearchGUI::on_searchButton_clicked()
{
    if (ui_->searchButton->text() == "Stop Searching")
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        rss_search_thread_->stopThread();
        ui_->searchButton->setText("Search");
        ui_->label->setText("");
        QApplication::restoreOverrideCursor();
    }
    else if (ui_->searchButton->text() == "Search")
    {
        rss_search_thread_->stopThread();
        ui_->searchButton->setText("Stop Searching");
        QString url = ui_->lineEdit->text();
        convertBigEndianToLittleEndian(url);

        rss_search_thread_->insertUrlDB(url);
        rss_search_thread_->setInitialUrl(url);

        if (!rss_search_thread_->setUrlRoot(url))
        {
            ui_->searchButton->setText("Search");
            QMessageBox::critical(nullptr, "Error",  "Invalid URL!");
            return;
        }
        else
        {
            rss_search_thread_->start();
        }
    }
}

void RSSSearchGUI::onFoundRSS(QString name
                              , const QString &url
                              , const QString &encoding
                              , const QString &web_source
                              , const int version) //event function, when found rss
{
    std::map<QString, std::shared_ptr<RSSData> >::iterator it;

    if (checkExistingURL(url))
    {
        return;
    }

    is_user_edit_ = false;
    parse_rss_->convertString(name, false);

    //ToDo: insert name
    it = rss_data_.find(name);
    while (it != rss_data_.end())
    {
        name = changeName (name);
        it = rss_data_.find(name);
    }

    std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData>();
    rss_data->setSiteName(name);
    rss_data->setURL(url);


    if (!version)
    {
        rss_data->setVersion(0);
        rss_data->setEncoding(encoding);
        parse_rss_->getArticlesFromRSSContent(web_source, rss_data);
    }
    else
    {
        rss_data->setVersion("2005");
        parse_rss_->getArticlesFromRDFContent(web_source, rss_data);
    }
    rss_data_[name] = rss_data;

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
    is_user_edit_ = true;
}

void RSSSearchGUI::onChangeUrlLabel (QString url)
{
    returnModifedString(url);
    ui_->label->setText(url);
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

void RSSSearchGUI::on_removeButton_clicked() //'Remove' button clicked
{
    QModelIndexList indexes = ui_->tableView->selectionModel()->selectedRows();
    qSort(indexes.begin(), indexes.end());
    while (!indexes.isEmpty())
    {
        model_->removeRows(indexes.last().row(), 1);
        //ToDo: remove the data from rss_data_

        indexes.removeLast();
    }
    paintRows();
}

void RSSSearchGUI::on_addRssFeeds_clicked() //"add RSS feeds" button
{
    this->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    std::map <QString, std::shared_ptr<RSSData>>::iterator it;

    for(it = rss_data_.begin(); it!=rss_data_.end(); ++it)
    {
        data_base_.insertIntoFeedList(it->second->getSiteName(), it->second->getURL(), it->second->getVersion());
        data_base_.insertIntoNewRssFeeds(it->second->getSiteName(), it->second->getURL(), it->second->getVersion());
    }

    QApplication::restoreOverrideCursor();

    if (rss_data_.size()>0)
    {
        emit (stateChanged("AddNewRSSData")); //Download the new rss data.
    }

    rss_data_.clear();

    this->setEnabled(true);

    emit (stateChanged("HideRssSearchWindow")); //There are not updates. Hide rss search window.
}


int RSSSearchGUI::isFeedChecked(const QString &url, int &index)
{
    for(int i = 0; i<model_->rowCount(); ++i)
    {
        //check for existing url
        if (model_->item(i,1)->text() == url )
        {
            index = i;
            QModelIndex index= ui_->tableView->model()->index(i,3, QModelIndex());
            if(index.data(Qt::CheckStateRole) == Qt::Checked)
            {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

QString RSSSearchGUI::changeName(const QString &name)
{
    QString result = name;
    if (result.length()<1)
    {
        result+="1";
        return result;
    }

    int n =  result[result.length()-1].unicode();
    //qDebug()<<result[index];
    if (n<48 || n>57)
    {
        result+="1";
        return result;
    }

    int number = 0;
    int multiple = 1;
    int num_len = 0;
    for (int i=result.length()-1; i>=0; i--)
    {
        int num = result[i].unicode();
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
    {
        result+="0";
    }

    int j=result.length()-1;
    for (int i = num_str.length()-1; i>=0; i--)
    {
        result[j--] = num_str[i];
    }

    return result;
}

void RSSSearchGUI::on_modelItemChanged(QStandardItem*item)
{
    /*
    bool in_if=false;
    if (item->column() == 0 && is_user_edit_ && !is_program_edit_)
    {
        //check name and make unique
        QString name  = item->text();

        while(treeContains(tree_node_,name))
            name = change_name(name); //make unique name

        editNode(tree_node_, old_names_[item->row()],name);
        old_names_[item->row()] = name;

        if (name != item->text())
        {
            is_program_edit_ = true;
            in_if = true;
            model_->setData(model_->index(item->row(),0),name); //set new name
        }
    }
    if (is_program_edit_ && !in_if)
        is_program_edit_ = false;
        */
}

void RSSSearchGUI::setupGui ()
{
     ui_->setupUi(this);

     this->setMinimumHeight(200);
     this->setMinimumWidth(350);

     //init gryd layout
     grid_->addWidget(ui_->lineEdit,0,0);
     grid_->addWidget(ui_->searchButton,0,1);
     grid_->addWidget(ui_->tableView,1,0);
     grid_->addWidget(ui_->addRssFeeds,3,0);
     grid_->addWidget(ui_->removeButton,1,1);
     grid_->addWidget(ui_->label,2,0);
     this->setLayout(grid_.get());

     //init QStandardItemModel and set it to ui->tableView (QTableView var)

     model_->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
     model_->setHorizontalHeaderItem(1, new QStandardItem(QString("URL")));
     model_->setHorizontalHeaderItem(2, new QStandardItem(QString("Encoding")));

     model_->setHorizontalHeaderItem(3, new QStandardItem(QString("Add to list")));
     ui_->tableView->setModel(model_.get());

     //start thread
     rss_search_thread_ = new RSSSearchGUIThread();

     connect(rss_search_thread_
             , SIGNAL(changeUrlLabel(QString))
             , this
             , SLOT(onChangeUrlLabel(QString))
             , Qt::QueuedConnection);

     connect(rss_search_thread_
             , SIGNAL(foundRSS(QString, const QString &, const QString &, const QString &, const int))
             , this
             , SLOT(onFoundRSS(QString, const QString &, const QString &, const QString &, const int))
             , Qt::QueuedConnection);

     connect(rss_search_thread_
             , SIGNAL(endOfUrls())
             ,this, SLOT(onEndOfUrls()));

     //init ui->tableView item changed event
     connect(model_.get(), SIGNAL(itemChanged(QStandardItem*)), this, SLOT(on_modelItemChanged(QStandardItem*)));

     ui_->label->setText("");
     is_user_edit_ = true;
     is_program_edit_ = false;
}

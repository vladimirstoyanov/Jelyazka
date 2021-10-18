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
    , add_id_           (3)
    , data_base_        ()
    , encoding_id_      (2)
    , grid_             (std::make_shared<QGridLayout> ())
    , model_            (std::make_shared<QStandardItemModel>(0,3,this))
    , name_id_          (0)
    , parse_rss_        (std::make_shared <ParseRSS> ())
    , ui_               (std::make_shared<Ui::RSSSearchGUI> ())
    , url_id_           (1)

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
        if (0 == i%2)
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

bool RSSSearchGUI::isUrlExist(const QString &url)
{
    QString itemText = "";
    for(int i = 0; i<model_->rowCount(); ++i)
    {
       itemText =  model_->item(i,url_id_)->text();
       if (url == itemText)
       {
            return true;
       }
    }
    return false;
}


void RSSSearchGUI::convertUppercaseToLowercase(QString &url)
{
    url = url.toLower();
}

void RSSSearchGUI::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key_Enter == event->key()) //'enter' button
    {
        ui_->searchButton->click();
    }
}

void RSSSearchGUI::showEvent(QShowEvent *)
{
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    rss_data_.clear();
    data_base_.removeAllDataFromNewRssFeeds();
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
        convertUppercaseToLowercase(url);

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

void RSSSearchGUI::setRssFeeds (const QString &web_source, std::shared_ptr<RSSData> rss_data)
{
    if ("" == rss_data->getVersion())
    {
        parse_rss_->getArticlesByRssContent(web_source, rss_data);
    }
    else
    {
        parse_rss_->getArticlesByRdfContent(web_source, rss_data);
    }
}

void RSSSearchGUI::onFoundRSS(QString name
                              , const QString &url
                              , const QString &encoding
                              , const QString &web_source
                              , const int version)
{
    if (isUrlExist(url))
    {
        return;
    }

    parse_rss_->convertString(name, false);
    std::shared_ptr<RSSData> rss_data = std::make_shared<RSSData>(name, url, encoding, version);
    setRssFeeds (web_source, rss_data);
    rss_data_[name] = rss_data;

    int row_count = model_->rowCount();
    model_->setRowCount(row_count+1);
    model_->setData(model_->index(row_count,name_id_),name);
    model_->setData(model_->index(row_count,url_id_),url);
    model_->setData(model_->index(row_count,encoding_id_),encoding);

    QStandardItem* item0 = new QStandardItem(true);
    item0->setCheckable(true);
    item0->setCheckState(Qt::Checked);

    item0->setEditable(false);
    model_->setItem(row_count, 3, item0);

    model_->item(model_->rowCount()-1,name_id_)->setEditable(false);
    model_->item(model_->rowCount()-1,url_id_)->setEditable(false);
    model_->item(model_->rowCount()-1,encoding_id_)->setEditable(false);

    paintRows();

    ui_->tableView->scrollToBottom();
    ui_->tableView->resizeColumnToContents(0);
}

void RSSSearchGUI::onChangeUrlLabel (QString url)
{
    modifyStringToFitWindowSize(url);
    ui_->label->setText(url);
}

void RSSSearchGUI::modifyStringToFitWindowSize(QString &str)
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

void RSSSearchGUI::removeRssData (const QString &name)
{
    if (rss_data_.find(name)!=rss_data_.end())
    {
        rss_data_.erase(name);
    }
}
void RSSSearchGUI::on_removeButton_clicked() //'Remove' button clicked
{
    QModelIndexList indexes = ui_->tableView->selectionModel()->selectedRows();
    qSort(indexes.begin(), indexes.end());
    while (!indexes.isEmpty())
    {
        removeRssData(indexes.last().data().toString());
        model_->removeRows(indexes.last().row(), 1);
        indexes.removeLast();
    }
    paintRows();
}

void RSSSearchGUI::on_addRssFeeds_clicked() //"add RSS feeds" button
{
    this->setEnabled(false);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    for (auto &item: rss_data_)
    {
        if (isRssFeedChecked(item.second->getURL()))
        {
            data_base_.insertIntoFeedList(item.second->getSiteName(), item.second->getURL(), item.second->getVersion());
            data_base_.insertIntoNewRssFeeds(item.second->getSiteName(), item.second->getURL(), item.second->getVersion());
        }
    }

    if (rss_data_.size()>0)
    {
        emit (stateChanged("AddNewRSSData")); //Download the new rss data.
    }

    rss_data_.clear();
    this->setEnabled(true);
    QApplication::restoreOverrideCursor();
    emit (stateChanged("HideRssSearchWindow")); //Hide rss search window.
}


bool RSSSearchGUI::isRssFeedChecked(const QString &url)
{
    for(int i = 0; i<model_->rowCount(); ++i)
    {
        if (model_->item(i,url_id_)->text() == url )
        {
            QModelIndex index= ui_->tableView->model()->index(i, add_id_, QModelIndex());
            if(index.data(Qt::CheckStateRole) == Qt::Checked)
            {
                return true;
            }
            return false;
        }
    }
    return false;
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

     model_->setHorizontalHeaderItem(name_id_, new QStandardItem(QString("Name")));
     model_->setHorizontalHeaderItem(url_id_, new QStandardItem(QString("URL")));
     model_->setHorizontalHeaderItem(encoding_id_, new QStandardItem(QString("Encoding")));
     model_->setHorizontalHeaderItem(add_id_, new QStandardItem(QString("Add")));
     ui_->tableView->setModel(model_.get());

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
}

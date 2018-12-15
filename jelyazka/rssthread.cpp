/*
    rssthread.cpp
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
#include "rssthread.h"

RSSThread::RSSThread(Data *data)
    : QRunnable()
{
    data_ = data;
    parse_rss_ = new ParseRSS(data);
    first_load_ = false;
    is_add_option_ = true;

    network_proxy_ = NULL;

    data_base_.loadStrctureFromDB (data);

    mutex_ = new QMutex();
    thread_pool_ = new QThreadPool(this);
    thread_pool_->setMaxThreadCount(5);

    loadOptions();
    setProxySettings();

    busy_ = false;
    data_for_animatewindow_ = "";
}

RSSThread::~RSSThread()
{
    delete mutex_;
    if (network_proxy_!=NULL)
        delete network_proxy_;
}

void RSSThread::synchronizeData(int struct_index, QString content)
{
    int index = 0;

    QList <RSSArticle> tmp_struct;

    if (data_->size()<=struct_index)
        return;

    if (data_->at(struct_index)->getArticlesSize()==0) //if articles list is empty
    {
        if(data_->at(struct_index)->getVersion() == "2005")
            parse_rss_->getArticlesFromRDFContent(content,  data_->at(struct_index));
        else
            parse_rss_->getArticlesFromRSSContent(content,  data_->at(struct_index));

        return;
    }

    RSSArticle ar;
    if(data_->at(struct_index)->getVersion() == "2005")
        parse_rss_->findFeedDataRDF(index,content,ar);//findSiteDataRSS2(index, content, ar);
    else
        parse_rss_->findFeedDataRSS(index, content,  ar);
    while (ar.getLink() != data_->at(struct_index)->articleAt(0).getLink() && index!=-1) //synchronize
    {
        tmp_struct.push_back(ar);
        if(data_->at(struct_index)->getVersion() == "2005")
            parse_rss_->findFeedDataRDF(index,content, ar);
        else
            parse_rss_->findFeedDataRSS(index, content, ar);
    }

    if (tmp_struct.size()==0)
        return;

    if (tmp_struct.size()>0 && enabled_notification_window_)
    {
       data_for_animatewindow_ += "<index=" + QString::number(struct_index) + ">";
    }

    //adding new data
    for (int i=0; i<tmp_struct.size(); i++)
    {
        if (INT_MAX<=data_->at(struct_index)->getArticlesSize())
            data_->at(struct_index)->eraseArticleAt(data_->at(struct_index)->getArticlesSize()-1);
        data_->at(struct_index)->articlesPushFront(tmp_struct[i]);
    }

}

void RSSThread::run() //runnning another thread (synchronize data for n time)
{
    HTTP http;
    QString content;

    mutex_->lock();
    int index=-1;
    for (uint i=0; i<data_->size(); i++)
    {
        if (!data_->at(i)->getIsRead())
        {
            index = i;
            data_->at(i)->setIsRead(true);// = true;
            break;
        }
    }
    mutex_->unlock();
    if (index == -1)
        return;

    content = "";
    if (http.getQuery(data_->at(index)->getURL(),content))
    {
        qDebug()<<data_->at(index)->getURL() + ": http get query has been failed!";
        mutex_->lock();
        data_->at(index)->setIsLoaded(true); //= true;
        if (!checkIsLoaded())
        {
            mutex_->unlock();
            return;
        }
        mutex_->unlock();
        return;
    }
    mutex_->lock();
    if (first_load_ == 0)
        emit loadRSS(data_->at(index)->getSiteName(), data_->at(index)->getURL());
    if (is_add_option_ == 0)
        emit Finish(data_->at(index)->getSiteName(), 0);
    synchronizeData(index, content);
    qDebug()<<"index:" + QString::number(index) + "url:" + data_->at(index)->getURL() + " count:"  + QString::number(data_->at(index)->getArticlesSize());
    data_->at(index)->setIsLoaded(true);// = true;
    checkIsLoaded();
    mutex_->unlock();
}

void RSSThread::setProxySettings()
{
    if (network_proxy_!=NULL)
        delete network_proxy_;

    if (!enabled_proxy_connection_)
        return;

    int port = proxy_port_.toInt();
    if (proxy_url_ == "" || port<1 || port>65536)
        return;

    network_proxy_ = new QNetworkProxy();
    network_proxy_->setType(QNetworkProxy::HttpProxy);
    network_proxy_->setHostName(proxy_url_);
    network_proxy_->setPort(port);
    QNetworkProxy::setApplicationProxy(*network_proxy_);
}

void RSSThread::emitAnimateWindow()
{
    emit showAnimateWindow(data_for_animatewindow_);
}

int RSSThread::checkIsLoaded()
{
    uint count = 0;

    for (uint i = 0; i< data_->size(); i++)
        if (data_->at(i)->getIsLoaded())
            count++;


    if (count == data_->size() && first_load_ == false)
    {
        first_load_ = true;
        emit loadRSS("","");
        return 0;
    }

    if (count == data_->size() && is_add_option_ == false)
    {
        emit Finish("", true);
        is_add_option_ = true;
        return 0;
    }
    return 1;
}

RSSData * RSSThread::initStruct(QString site_name, QString type, QString url)
{
    RSSData *s = new RSSData();

    s->setSiteName(site_name);
    s->setType(type);
    s->setURL(url);

    return s;
}

void RSSThread::loadOptions()
{
    QFile file("../resources/Options");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, "Error!", file.errorString());
    }

    QTextStream in(&file);

    QString what ="";
    QString line = in.readLine();

    if (line.length()<14)
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }
    if (line[13] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }

    int i=14;
    while (line[i] != '\n' && i<line.length())
    {
        what+=line[i];
        i++;
    }
    i = what.toInt();
    refresh_time_feeds_ = i;

    line = in.readLine();

    if (line.length()<21)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[20] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }

    if (line[21]=='0')
        enabled_notification_window_ = false;
    else if (line[21] == '1')
        enabled_notification_window_ = true;
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from a \'Options\' file!");

    // enable/dissable proxy connection
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[14] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for enable proxy connection from \'Options\' file!");
        file.close();
        return;
    }

    if (line[15]=='0')
        enabled_proxy_connection_ = false;
    else if (line[15] == '1')
        enabled_proxy_connection_ = true;
    else
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from a \'Options\' file!");

    //proxy url
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        return;
    }

    if (line[14]!=' ')
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        return;
    }

    i=15;
    QString str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    proxy_url_ = str_tmp;

    //laod proxy port information
    line = in.readLine();
    if (line.length()<12)
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy port in \'Options\' file!");
        return;
    }
    if (line[11]!=' ')
    {

        QMessageBox::critical(0, "Error!", "Something is wrong with proxy port in \'Options\' file!");
        return;
    }
    i=12;
    str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    proxy_port_ = str_tmp;

    file.close();
}

void RSSThread::setRefreshTime(int refresh_time_feeds)
{
    this->refresh_time_feeds_ = refresh_time_feeds;
}

void RSSThread::setEnableNotificationWindow(bool enabled_notification_window)
{
    this->enabled_notification_window_ = enabled_notification_window;
}

bool RSSThread::getEnabledNotificationWindow()
{
    return enabled_notification_window_;
}

int RSSThread::getRefreshTime()
{
    return refresh_time_feeds_;
}

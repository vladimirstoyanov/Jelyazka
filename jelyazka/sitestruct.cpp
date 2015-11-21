/*
    sitestruct.cpp
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
#include "sitestruct.h"

SiteStruct::SiteStruct(Data *data_tmp)
    : QRunnable()
{
    data = data_tmp;
    parseRSS = new ParseRSS(data);
    first_load = false;
    isAddOption = true;

    network_proxy = NULL;

    db.loadStrctureFromDB (data);

    mutex = new QMutex();
    tp = new QThreadPool(this);
    tp->setMaxThreadCount(5);

    loadOptions();
    setProxySettings();

    busy = false;
    data_for_animatewindow = "";
}

SiteStruct::~SiteStruct()
{
    delete mutex;
    if (network_proxy!=NULL)
        delete network_proxy;
}

void SiteStruct::synchronizeData(int struct_index, QString content)
{
    int index = 0;

    QList <RSSArticle> tmp_struct;

    if (data->size()<=struct_index)
        return;

    if (data->at(struct_index)->getArticlesSize()==0) //if articles list is empty
    {
        if(data->at(struct_index)->getVersion() == "2005")
            parseRSS->getArticlesFromRDFContent(content,  data->at(struct_index));
        else
            parseRSS->getArticlesFromRSSContent(content,  data->at(struct_index));

        return;
    }

    RSSArticle ar;
    if(data->at(struct_index)->getVersion() == "2005")
        parseRSS->findFeedDataRDF(index,content,ar);//findSiteDataRSS2(index, content, ar);
    else
        parseRSS->findFeedDataRSS(index, content,  ar);
    while (ar.getLink() != data->at(struct_index)->articleAt(0).getLink() && index!=-1) //synchronize
    {
        tmp_struct.push_back(ar);
        if(data->at(struct_index)->getVersion() == "2005")
            parseRSS->findFeedDataRDF(index,content, ar);
        else
            parseRSS->findFeedDataRSS(index, content, ar);
    }

    if (tmp_struct.size()==0)
        return;

    if (tmp_struct.size()>0 && enabled_notification_window)
    {
       data_for_animatewindow += "<index=" + QString::number(struct_index) + ">";
    }

    //adding new data
    for (int i=0; i<tmp_struct.size(); i++)
    {
        if (INT_MAX<=data->at(struct_index)->getArticlesSize())
            data->at(struct_index)->eraseArticleAt(data->at(struct_index)->getArticlesSize()-1);
        data->at(struct_index)->articlesPushFront(tmp_struct[i]);
    }

}

void SiteStruct::run() //runnning another thread (synchronize data for n time)
{
    HTTP http;
    QString content;

    mutex->lock();
    int index=-1;
    for (uint i=0; i<data->size(); i++)
    {
        if (!data->at(i)->getIsRead())
        {
            index = i;
            data->at(i)->setIsRead(true);// = true;
            break;
        }
    }
    mutex->unlock();
    if (index == -1)
        return;

    content = "";
    if (http.getQuery(data->at(index)->getURL(),content))
    {
        qDebug()<<data->at(index)->getURL() + ": http get query has been failed!";
        mutex->lock();
        data->at(index)->setIsLoaded(true); //= true;
        if (!checkIsLoaded())
        {
            mutex->unlock();
            return;
        }
        mutex->unlock();
        return;
    }
    mutex->lock();
    if (first_load == 0)
        emit loadRSS(data->at(index)->getSiteName(), data->at(index)->getURL());
    if (isAddOption == 0)
        emit Finish(data->at(index)->getSiteName(), 0);
    synchronizeData(index,content);
    qDebug()<<"index:" + QString::number(index) + "url:" + data->at(index)->getURL() + " count:"  + QString::number(data->at(index)->getArticlesSize());
    data->at(index)->setIsLoaded(true);// = true;
    checkIsLoaded();
    mutex->unlock();
}

void SiteStruct::setProxySettings()
{
    if (network_proxy!=NULL)
        delete network_proxy;

    if (!enabled_proxy_connection)
        return;

    int port = proxy_port.toInt();
    if (proxy_url == "" || port<1 || port>65536)
        return;

    network_proxy = new QNetworkProxy();
    network_proxy->setType(QNetworkProxy::HttpProxy);
    network_proxy->setHostName(proxy_url);
    network_proxy->setPort(port);
    QNetworkProxy::setApplicationProxy(*network_proxy);
}

void SiteStruct::emitAnimateWindow()
{
    emit showAnimateWindow(data_for_animatewindow);
}

int SiteStruct::checkIsLoaded()
{
    uint count = 0;

    for (uint i = 0; i< data->size(); i++)
        if (data->at(i)->getIsLoaded())
            count++;


    if (count == data->size() && first_load == false)
    {
        first_load = true;
        emit loadRSS("","");
        return 0;
    }

    if (count == data->size() && isAddOption == false)
    {
        emit Finish("", true);
        isAddOption = true;
        return 0;
    }
    return 1;
}

RSSData * SiteStruct::initStruct(QString site_name, QString type, QString url)
{
    RSSData *s = new RSSData();

    s->setSiteName(site_name);
    s->setType(type);
    s->setURL(url);

    return s;
}

void SiteStruct::loadOptions()
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
    refresh_time_feeds = i;

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
        enabled_notification_window = false;
    else if (line[21] == '1')
        enabled_notification_window = true;
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
        enabled_proxy_connection = false;
    else if (line[15] == '1')
        enabled_proxy_connection = true;
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

    proxy_url = str_tmp;

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

    proxy_port = str_tmp;

    file.close();
}

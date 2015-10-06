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

SiteStruct::SiteStruct(QObject *parent)
    : QRunnable()
{
    first_load = false;
    isAddOption = true;
    //aw->show();

    network_proxy = NULL;

    //open db
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("sites.db3");
    sqliteDataBase.open();

    loadStrctureFromDB();

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
    sqliteDataBase.close();
    delete mutex;
    if (network_proxy!=NULL)
        delete network_proxy;
}

void SiteStruct::loadStrctureFromDB()
{
    QSqlQuery query;

    createTables();

    //get all rss feeds urls
    query.prepare( "SELECT * FROM favorite_feeds" );

    if( !query.exec() )
    {
        qDebug()<<"Some error, when trying to read from \'favorite_feeds\' table...";
        return;
    }

    while( query.next() )
    {
        RSSData *rssData = new RSSData();
        rssData->setSiteName(query.value( 1 ).toByteArray().data());
        rssData->setURL(query.value( 2 ).toByteArray().data());
        rssData->setType("RSS");
        rssData->setVersion(query.value(3).toByteArray().data());
        s_struct.push_back(rssData);
    }
}

void SiteStruct::synchronizeData(int struct_index, QString content)
{
    int index = 0;

    QList <RSSArticle> tmp_struct;

    if (s_struct.size()<=struct_index)
        return;

    if (s_struct[struct_index].getArticlesSize()==0) //if articles list is empty
    {
        if(s_struct[struct_index].getVersion() == "2005")
            getArticlesForIndexRSS2(content,struct_index);
        else
            getArticlesForIndexRSS(content,struct_index);
        return;
    }

    RSSArticle ar;
    if(s_struct[struct_index].getVersion() == "2005")
         findSiteDataRSS2(index, content, ar);
    else
        findSiteDataRSS(index, content,  ar);
    while (ar.getLink() != s_struct[struct_index].articleAt(0).getLink() && index!=-1) //synchronize
    {
        tmp_struct.push_back(ar);
        if(s_struct[struct_index].getVersion() == "2005")
            findSiteDataRSS2(index,content, ar);
        else
            findSiteDataRSS(index, content, ar);
    }

    if (tmp_struct.size()==0)
        return;

    if (tmp_struct.size()>0 && enabled_notification_window)
    {
       data_for_animatewindow += "<index=" + QString::number(struct_index) + ">";
    }

    //adding new data
    for (uint i=0; i<tmp_struct.size(); i++)
    {
        if (INT_SIZE<=s_struct.at(struct_index).getArticlesSize())
            s_struct.at(struct_index).eraseArticleAt(s_struct.at(struct_index).getArticlesSize()-1);
        s_struct.at(struct_index).articlesPushFront(tmp_struct[i]);
    }

}

void SiteStruct::findSiteDataRSS(int &index, QString content, RSSArticle &ar) //QString &title, QString &link, QString &text)
{
    int item_b_index=index, item_e_index=index;
    CSearch cs;
    int n = content.length();

    while (1)
    {
         cs.search_After(content,"<item", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.search_Before(content,"</item", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         if (item_b_index<n)
         {
             if (content[item_b_index] == 's') //if found <items tag
                 continue;
         }
         index = item_e_index;
         break;
    }

    index = item_e_index;
    QString title, link, text;

    if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
         return;
    convert_string(title, false);
    if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
         return;
    convert_string(link, true);
    getDescription(item_b_index, item_e_index, text, content);

    ar.setLink(link);
    ar.setText(text);
    ar.setTitle(title);
}

void SiteStruct::findSiteDataRSS2(int &index, QString content, RSSArticle &ar)// QString &title, QString &link, QString &text)
{
    int item_b_index=index, item_e_index=index;
    CSearch cs;

     while (1)
     {
         cs.search_After(content,"<entry", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.search_Before(content,"</entry", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         index = item_e_index;
         break;
     }

     index = item_e_index;
     QString title, link, text;

     if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
         return;
     convert_string(title, false);
     int index_link = item_b_index;
     cs.search_Before(content, "<link", &index_link);
     if (index_link == -1 || index_link>item_e_index)
         return;
     link = returnURL(content, index_link);
     convert_string(link, true);

     getContent(item_b_index, item_e_index, text, content);

     ar.setLink(link);
     ar.setText(text);
     ar.setTitle(title);
}

void SiteStruct::run() //runnning another thread (synchronize data for n time)
{
    Net net;
    QString content;

    mutex->lock();
    int index=-1;
    for (uint i=0; i<s_struct.size(); i++)
    {
        if (!s_struct.at(i).getIsRead())
        {
            index = i;
            s_struct.at(i).setIsRead(true);// = true;
            break;
        }
    }
    mutex->unlock();
    if (index == -1)
        return;

    content = "";
    if (net.getQuery(s_struct.at(index).getURL(),content))
    {
        qDebug()<<s_struct.at(index).getURL() + ": http get query has been failed!";
        mutex->lock();
        s_struct.at(index).setIsLoaded(true); //= true;
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
        emit loadRSS(s_struct.at(index).getSiteName(), s_struct.at(index).getURL());
    if (isAddOption == 0)
        emit Finish(s_struct[index].getSiteName(), 0);
    synchronizeData(index,content);
    qDebug()<<"index:" + QString::number(index) + "url:" + s_struct[index].getURL() + " count:"  + QString::number(s_struct[index].getArticlesSize());
    s_struct[index].setIsLoaded(true);// = true;
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

void SiteStruct::createTables()
{
    //"collec_feeds" table
    if (!sqliteDataBase.tables().contains(QLatin1String("collect_feeds"))) //if hasn't 'collect_feeds' table
    {
        //create 'collect_feeds'table
        if (sqliteDataBase.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table collect_feeds "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "name varchar, "
                          "url varchar, "
                          "version integer)"))
                {
                    qDebug()<<"Can't create table: collect_feeds";
                }
        }
    }

    //"all_urls" table
    if (!sqliteDataBase.tables().contains(QLatin1String("all_urls"))) //if hasn't 'all_urls' table
    {
        //create 'collect_feeds' table
        if (sqliteDataBase.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table all_urls "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "url varchar)"))
                {
                    qDebug()<<"Can't create table: all_urls";
                }
        }
    }

    //"rss" table
    if (!sqliteDataBase.tables().contains(QLatin1String("favorite_feeds"))) //if hasn't 'rss' table
    {
        //create 'rss'table
        if (sqliteDataBase.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table favorite_feeds "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "name varchar, "
                          "url varchar, "
                          "version integer)"))
                {
                     qDebug()<<"Can't create table: rss";
                }
        }
    }

    //"filter" table
    if (!sqliteDataBase.tables().contains(QLatin1String("filters"))) //if hasn't 'rss' table
    {
        //create 'rss' table
        if (sqliteDataBase.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table filters "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "filter varchar)"))
                {
                     qDebug()<<"Can't create table: filters";
                }
        }
    }
}

//Get articles from rss source
int SiteStruct::getArticlesForIndexRSS(QString content,uint struct_index)
{
    int item_b_index=0, item_e_index=0;
    CSearch cs;
    int n = content.length();

    while(1)
    {
        cs.search_After(content,"<item", &item_b_index);
        if (item_b_index == -1)
            break;

        item_e_index = item_b_index;
        cs.search_Before(content,"</item", &item_e_index);

        if (item_e_index == -1)
            break;

        if (item_b_index<n)
        {
            if (content[item_b_index] == 's') //if found <items tag
                continue;
        }

        QString title, link, text;
        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
            break;
        convert_string(title, false);
        if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
            break;

        convert_string(link, true);
        getDescription(item_b_index, item_e_index, text, content);

        RSSArticle art;
        art.setLink(link);
        art.setText(text);
        art.setTitle(title);

        if (INT_SIZE <= s_struct[struct_index].getArticlesSize()) //prevent int overflow
        {
            s_struct[struct_index].eraseArticleAt(s_struct[struct_index].getArticlesSize()-1);
            s_struct[struct_index].articlesPushFront(art);
            continue;
        }

        s_struct[struct_index].articlesPushBack(art);
    }
    return 0;
}

//Get articles from rdf xml
int SiteStruct::getArticlesForIndexRSS2(QString content,uint struct_index)
{
    int item_b_index=0, item_e_index=0;
    CSearch cs;
    //int n = content.length();

    while(1)
    {
        cs.search_After(content,"<entry", &item_b_index);
        if (item_b_index == -1)
            break;

        item_e_index = item_b_index;
        cs.search_Before(content,"</entry", &item_e_index);

        if (item_e_index == -1)
            break;

        QString title, link, text;

        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
            break;
        convert_string(title, false);

        int index_link = item_b_index;
        cs.search_Before(content, "<link", &index_link);
        if (index_link == -1 || index_link>item_e_index)
            break;
        link = returnURL(content, index_link);
        convert_string(link, true);
        getContent(item_b_index, item_e_index, text, content);

        RSSArticle art;
        art.setLink(link);
        art.setText(text);
        art.setTitle(title);

        if (INT_SIZE <= s_struct[struct_index].getArticlesSize()) //prevent int overflow
        {
            s_struct[struct_index].eraseArticleAt(s_struct[struct_index].getArticlesSize()-1);
            s_struct[struct_index].articlesPushFront(art);
            continue;
        }

        s_struct[struct_index].articlesPushBack(art);

    }
    return 0;
}

int SiteStruct::getTextBetweenIndexes(int item_b_index, int item_e_index, QString begin_text, QString end_text, QString &text, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,begin_text, &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, end_text, &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;


    if (begin_text[begin_text.length()-1] != '>')//version == 2005
    {
        while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
            tag_b_index++;
        tag_b_index++;
    }

    text = "";
    for (int i=tag_b_index; i <tag_e_index; i++)
        text+=content[i];

    return 0;

}

int SiteStruct::getDescription(int item_b_index, int item_e_index, QString &description, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,"<description>", &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, "</description>", &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;


    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.search_After(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                    return 1;
                if (index_tmp <= tag_e_index)
                    i = index_tmp-1;
                continue;
            }
        }
        if (cdata && content[i]=='[')
            continue;
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
                break;
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!' && content[i+2] == '[' && content[i+3] == 'C' && content[i+4] == 'D' && content[i+5] == 'A' && content[i+6] == 'T' && content[i+7] == 'A' && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

int SiteStruct::getContent(int item_b_index, int item_e_index, QString &description, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,"<content", &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, "</content>", &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;

    while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
        tag_b_index++;
    tag_b_index++;

    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.search_After(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                    return 1;
                if (index_tmp <= tag_e_index)
                    i = index_tmp-1;
                continue;
            }
        }
        if (cdata && content[i]=='[')
            continue;
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
                break;
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!' && content[i+2] == '[' && content[i+3] == 'C' && content[i+4] == 'D' && content[i+5] == 'A' && content[i+6] == 'T' && content[i+7] == 'A' && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

int SiteStruct::checkIsLoaded()
{
    uint count = 0;

    for (uint i = 0; i< s_struct.size(); i++)
        if (s_struct[i].getIsLoaded())
            count++;


    if (count == s_struct.size() && first_load == false)
    {
        first_load = true;
        emit loadRSS("","");
        return 0;
    }

    if (count == s_struct.size() && isAddOption == false)
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

QString SiteStruct::convert_entitie(QString entitie)
{

    if (entitie == "&quot")
        return "\"";
    else if (entitie == "&nbsp" || entitie =="&#160")
        return " ";
    else if (entitie == "&amp" || entitie == "&#38")
        return "&";
    else if (entitie == "&lt" || entitie == "&#60")
        return "<";
    else if (entitie == "&qt" || entitie == "&#62")
        return ">";
    else if (entitie == "&OElig")
        return "Œ";
    else if (entitie == "&oelig")
        return "œ";
    else if (entitie == "&Scaron")
        return "Š";
    else if (entitie == "&scaron")
        return "š";
    else if (entitie == "&Yuml")
        return "Ÿ";
    else if (entitie == "&circ")
        return "ˆ";
    else if (entitie == "&tilde")
        return "~";
    else if (entitie == "&ndash")
        return "–";
    else if (entitie == "&ndash")
        return "–";
    else if (entitie == "&mdash")
        return "—";
    else if (entitie == "&lsquo")
        return "‘";
    else if (entitie == "&rsquo")
        return "’";
    else if (entitie == "&sbquo")
        return "‚";
    else if (entitie == "&ldquo")
        return "“";
    else if (entitie == "&rdquo")
        return "”";
    else if (entitie == "&bdquo")
        return "„";
    else if (entitie == "&dagger")
        return "†";
    else if (entitie == "&Dagger")
        return "‡";
    else if (entitie == "&permil")
        return "‰";
    else if (entitie == "&lsaquo")
        return "‹";
    else if (entitie == "&rsaquo")
        return "›";
    else if (entitie == "&euro" || entitie == "&#8364")
        return "€";
    else if (entitie == "&cent" || entitie == "&#162" )
        return "¢";
    else if (entitie == "&pound" || entitie == "&#163")
        return "£";
    else if (entitie == "&yen" || entitie == "&#165")
        return "¥";
    else if (entitie == "&copy" || entitie == "&#169")
        return "©";
    else if (entitie == "&reg" || entitie == "&#174")
        return "®";
    else
        return "";
}

void SiteStruct::convert_string (QString &str, bool link)
{
    QString entitie;
    QString str_tmp = "";
    bool cdata=false;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] == '&' && !link)
        {
            int c = i;
            entitie = "";
            while(str[i]!=';'&& i<str.length() && (i-c)<7)
            {
                entitie += str[i];
                i++;
            }
            QString conv = convert_entitie(entitie);
            if (conv == "")
                i=c;
            else
                str_tmp += conv;
            continue;
        }
        if (cdata && str[i] == ']')
        {
            cdata = false;
            if (i+2>=str.length())
                break;
            i+=2;
            continue;
        }
        if (str[i] == '<')
        {
            if (str.length()<=i+9)
            {
                str_tmp +=str[i];
                continue;
            }
            //<![CDATA["
            if (str[i+1] == '!' && str[i+2] == '[' && str[i+3] == 'C' && str[i+4] == 'D' && str[i+5] == 'A' && str[i+6] == 'T' && str[i+7] == 'A' && str[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        str_tmp+=str[i];
    }
    str = str_tmp;
}

QString SiteStruct::returnURL(QString source, int index)
{
    if (index <0 || index>source.length())
        return "";

    QString label = "href=";
    int n = source.length();
    int n1 = label.length();


    int j = 0;
    while (source[index]!='>' && index<n)
    {
        if (j==n1) //found 'href' before '>'
            break;

        if (source[index]!=label[j])
        {
            j=0;
            index++;
            continue;
        }
        j++;
        index++;
    }
    if (index >= n) //if not found href= in source
        return "";

    while (source[index]!='\"' && index<n)
        index++;
    index++;
    QString url = "";
    while (source[index]!='\"' && index<n)
        url+=source[index++];

    return url;
}

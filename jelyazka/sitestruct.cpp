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

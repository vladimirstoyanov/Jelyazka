/*
    web_search_interface_thread.cpp
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
#include "web_search_interface_thread.h"
#include "net.h"

WebSearchInterfaceThread::WebSearchInterfaceThread(QObject *parent) :
    QRunnable()
{
    stop_thread = false;
    mutex = new QMutex();
}

WebSearchInterfaceThread::~WebSearchInterfaceThread()
{
    if  (l_url.size()>0)
        l_url.clear();
    deleteAllFrom_all_url_table();
    delete mutex;
}

bool WebSearchInterfaceThread::setUrlRoot(QString url)
{
    Net n;
    CSearch cs;

    QString query_part="";
    n.queryPartAndURL(url,query_part);
    int index = 0;
    cs.search_Before(url, "www.", &index);

    if (index == 0) //remove 'www.'
    {
        url_root="";
        for (int i=4; i<url.length(); i++)
            url_root+=url[i];
    }
    else
        url_root = url;

    if (url_root == "")
        return 0;

    return 1;
}

void WebSearchInterfaceThread::run()
{
    if (stop_thread)
    {
        return;
    }

    CSearch cs;
    QString html;
    Net n;

    mutex->lock();
    if (l_url.size() == 0)
    {
        mutex->unlock();
        emit EndOfUrls();//onEndOfUrls load new URLs in l_url if l_url2.size()>0
        return;
    }
    QString *url = new QString(*l_url.begin());
    l_url.erase(l_url.begin());
    mutex->unlock();

    emit FoundRSS(1,*url,*url,"","",0); //this emit make ui->label->setText(url) from web_search_interface;

    int type = 0;

    if (n.getQuery(*url, html, type)) //if can't connect
    {
            mutex->lock();
            if(checkFinish())
                emit EndOfUrls();
            mutex->unlock();
            emit FoundRSS (1,"Fail to connect!", "Fail to connect!","","",0);
            delete url;
            return;
    }

    if (stop_thread)
    {
        delete url;
        return;
    }

    if (type == 2) //xml
    {
        QString title = "";
        int version = 0;
        if (!checkForRss(html, title, version)) //found rss
        {
                QString encoding  = getEncodingFromRSS(html);
                if (encoding =="")
                    encoding = "UTF-8";
                //log.write("==RSS==:" + *url, "log.txt");

                title = title.replace("\'","\"");
                *url = url->replace("\'","\"");
                encoding = encoding.replace("\'","\"");

                emit FoundRSS(0,title,*url, encoding, html, version);
        }
        mutex->lock();
        if (checkFinish())
            emit EndOfUrls();
        mutex->unlock();
        delete url;
        return;
    }

    int index = 0;

    while(index != -1)
    {
            if (stop_thread)
            {
                delete url;
                return;
            }

            //log.write("!!!cs.Search_After(&html, \"<a \",&index);");
            cs.search_After(html, "<a ",&index); //search for links

            while (lookForHref(html,index) && index!=-1)
                cs.search_After(html, "<a ",&index); //in case in tag 'a' haven't 'href'



            if (index!=-1)
            {
                getUrl(html,index, *url); //get url
                QString return_url;

                mutex->lock();

                buildUrl(url_root, *url, return_url);
                if (return_url == "") // if fail to build url
                {

                    log.write(*url  + "\n","ignore.txt");
                    mutex->unlock();
                    continue;

                }

                if (!findUrlDB(return_url))
                {

                     log.write(return_url, "log.txt");
                     QString *url_tmp = new QString(return_url);
                     l_url2.push_back(url_tmp);
                     if (return_url.length()>2047)
                         qDebug()<<"Lenght > 2047 !!!";
                     else
                     {
                         insertUrlDB(return_url);
                         //qDebug()<<"Added " + return_url;
                     }
                }
                mutex->unlock();
            }
    }
    //l_url.erase(l_url.begin()); //delete first element from vector

    mutex->lock();
    if(checkFinish())
        emit EndOfUrls();
    mutex->unlock();

    delete url;
}

//get url from html_source after index
void WebSearchInterfaceThread::getUrl (QString html_source, int &index, QString &return_url)
{
    return_url ="";
    while(index< html_source.length() && html_source[index]!='\"') //vol
        index++;
    index++;

    while(index< html_source.length() && html_source[index]!='\"') //vol
    {
        return_url+=html_source[index];
        index++;
    }

    if (return_url.length()>1 && return_url[0]=='/' && return_url[1]=='/') //vol
    {
        QString return_url_tmp = "";
        for (int i=2 ; i<return_url.length(); i++)
            return_url_tmp+=return_url[i];
        return_url = return_url_tmp;
    }
}

//Build full url name
void WebSearchInterfaceThread::buildUrl (QString url_root, QString url, QString &return_url)
{
    CSearch cs;
    return_url = "";

    for (int i=0; i<url.length(); i++)
    {
        if (int(url[i].toLatin1()) == 32) //if url has space, then replace with %20
        {
            return_url+="%20";
            continue;
        }
        if (url[i] == '\'' || url[i] == '\"')
        {
            return_url = "";
            return;
        }
        if (url[i] == '\n' || url[i] == '\r')
            continue;

        return_url+=url[i];
    }


    int ret  = 0, ret1 = 0;
    cs.search_Before(return_url,url_root, &ret); //search for root_url
    cs.search_After(return_url,"://", &ret1); //search for protocol
    if (ret == -1 && ret1 == -1  && return_url.length()>0)
    {
        if (url_root[url_root.length()-1] == '/' && return_url[0]!='/')
            return_url = url_root + return_url;
        else if (url_root[url_root.length()-1] != '/' && return_url[0]!='/')
            return_url = url_root + '/' + return_url;
        else if (url_root[url_root.length()-1] == '/' && return_url[0]=='/')
        {
            QString return_url_tmp = return_url;
            return_url ="";
            for (int i=1; i<return_url_tmp.length(); i++) //without '/'
                return_url+=return_url_tmp[i];
            return_url = url_root + return_url;
        }
        else
            return_url = url_root + return_url;
        return;
    }
    if (ret == -1)
    {
        return_url = "";
        return;
    }
    if (checkForRootURL(return_url,ret1,ret)) //if URL is from another web site
    {
        return_url = "";
        return;
    }
    if (ret1!=-1)
        fixProtocol(return_url);
}

int WebSearchInterfaceThread::fixProtocol(QString &url)
{
    CSearch cs;
    int index = 0;

    cs.search_Before(url, "http://", &index);

    if (index == -1 || index == 0)
        return 0;

    QString url_tmp = "";
    for (int i = index; i<url.length(); i++)
        url_tmp += url[i];

    url = url_tmp;

    return 1;
}

int WebSearchInterfaceThread::checkForRss(QString source, QString &title, int &version)
{
    CSearch cs;
    QString begin="<?xml";
    //Logger log;

    if (source.length()<4)
    {
        //log.write("CheckForRss funtion: source.length()<4!");
        return 1;
    }
    int i=0, j=0, r=0, f=0;
    cs.search_After(source, "<?xml", &i);
    cs.search_After(source, "<rss", &j);
    cs.search_After(source, "<rdf", &r);
    cs.search_After(source, "<feed", &f);

    if (i==0 || (j==-1 && r==-1 && f ==-1) || (j!=-1 && i>j) || (r!=-1 && i>r) || (f!=-1 && i>f))
        return 1;

    if (f!=-1 && j==-1 && r==-1)
        version = 2005;

    //get rss title
    i=0;
    cs.search_After(source, "<title>", &i);
    if (i==-1)
    {
        //log.write("CheckForRss funtion: can't find <title>");
        return 1;
    }

    title = "";
    int n = source.length();

    if (i>=n-2)
        return 1;

    if (source[i] == '<' && source[i+1] == '!') //ignoring '<![CDATA'
        title+=source[i++];

    while (source[i]!='<')
    {
        title+=source[i++];

        if (i>=n-2)
        {
            //log.write("CheckForRss funtion: fail to get </title>.");
            return 1;
        }
        if (source[i] == '<' && source[i+1] == '!') //ignoring '<![CDATA'
            title+=source[i++];
    }


    i++;
    begin = "/title";

    for(j=0;j<begin.length(); j++)
        if (source[i++]!=begin[j])
            return 1;

    return 0;
}

int WebSearchInterfaceThread::lookForHref(QString source, int &index)
{
    if (index <0)
        return 1;

    QString label = "href=";
    int old_index = index;
    int n = source.length();
    int n1 = label.length();


    int j = 0;
    while (source[index]!='>' && index<n)
    {
        if (j==n1) //found 'href' before '>'
            return 0;

        if (source[index]!=label[j])
        {
            j=0;
            index++;
            continue;
        }
        j++;
        index++;
    }
    if (index >= n) //if not found href= in entire html source
        index =-1;

    index = old_index;
    return 1;
}

void WebSearchInterfaceThread::addOrRemoveLastSymbolSlash(QString url, QString *new_url)
{
    if (url[url.length()-1]!='/')
        *new_url = url + '/';
    else //without '/'
    {

        for (int i=0; i<url.length()-1; i++)
            *new_url+=url[i];
    }
}

//i1 - index before root_url
//i - index after '://'
int WebSearchInterfaceThread::checkForRootURL(QString url, int i, int i1)
{
    if (i==-1)
        i=0;
    while (i<url.length() && url[i]!='/')
        i++;
    if (i1 < i)
        return 0;
    return 1;
}

int WebSearchInterfaceThread::insertUrlDB(QString url)//+
{
    return db.insertIntoAllURLs(url);
}

int WebSearchInterfaceThread::findUrlDB(QString url)
{
    return db.selectURLFromAllURLs(url);
}

int WebSearchInterfaceThread::deleteAllFrom_all_url_table() //delete all_url table
{
    return db.deleteAllFromAllURL();
}

QString WebSearchInterfaceThread::getEncodingFromRSS(QString content) //+
{
    CSearch cs;
    QString encoding="";
    int index1=0, index2=0;

    cs.search_After(content,"<?xml", &index1);

    if (index1 == -1)
        return "";

    cs.search_Before(content, "?>", &index2);

    if (index2 == -1)
        return "";

    cs.search_After(content, "encoding=", &index1);

    if (index1 == -1 || index1>index2)
        return "";

    while (content[index1]!='\'' && content [index1]!='\"' && index1<index2)
        index1++;

    index1++;
    while (content[index1]!='\'' && content [index1]!='\"' && index1<index2)
        encoding += content[index1++];

    return encoding;
}

int WebSearchInterfaceThread::checkFinish()
{
    int count = 0;
    for (int i = 0; i<l_flags.size(); i++)
    {
        if(l_flags[i] == 0)
        {
            l_flags[i] = 1;
            count++;
            break;
        }
        count++;
    }
    qDebug()<<QString::number(count) + "/" + QString::number(l_flags.size());

    if (count == l_flags.size())
        return 1;

    return 0;
}

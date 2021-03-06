/*
    rss_search_thread.cpp
    Jelyazka RSS/RDF reader
    Copyright (C) 2020 Vladimir Stoyanov

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
#include "rss_search_thread.h"

RSSSearchGUIThread::RSSSearchGUIThread() :
    is_search_finished_ (false)
    , max_count_of_pending_urls_ (5)
    , network_manager_(std::make_shared<NetworkManager> ())
    , pending_urls_(0)
    , stop_thread_ (false)
{
    setupConnections ();
}

RSSSearchGUIThread::~RSSSearchGUIThread()
{
    deleteAllFrom_all_url_table();
}
void RSSSearchGUIThread::stopThread ()
{
  stop_thread_ = true;
  pending_urls_ = 0;
  deleteAllFrom_all_url_table();
  while (!url_queue_.empty())
  {
      url_queue_.pop();
  }
}

void RSSSearchGUIThread::setInitialUrl (const QString &url)
{
  stop_thread_ = false;
  is_search_finished_  = false;
  url_queue_.push(url);
}

void RSSSearchGUIThread::run()
{
  while (1)
  {
      if (stop_thread_)
      {
          emit(changeUrlLabel (""));
          return;
      }

      if (!url_queue_.empty()) //we overload probably the http library
      {
        if (pending_urls_>max_count_of_pending_urls_)
        {
            usleep(100000); //100 milliseconds
            continue;
        }
        QString url = url_queue_.front();
        url_queue_.pop();

        emit (httpGetRequest(url));

        ++pending_urls_;
      }

      if (0 >= pending_urls_)
      {
          emit endOfUrls();
          return;
      }
      usleep(100000); //100 milliseconds
  }
}

void RSSSearchGUIThread::onHttpRequestReceived(const HttpData & httpData)
{
    qDebug()<<__PRETTY_FUNCTION__;
    Search cs;
    QString url = httpData.getUrl();

    --pending_urls_;

    if (!httpData.isResponseSuccessful())
    {
        return;
    }

    emit (changeUrlLabel(url));

    if (ContentType::XML == httpData.getContentType()) //xml
    {
        QString title = "";
        int version = 0;
        if (!checkForRss(httpData.getData(), title, version)) //found rss
        {
                QString encoding  = getEncodingFromRSS(httpData.getData());
                if (encoding =="")
                {
                    encoding = "UTF-8";
                }

                title = title.replace("\'","\"");
                url = url.replace("\'","\"");
                encoding = encoding.replace("\'","\"");

                emit foundRSS(title, url, encoding, httpData.getData(), version);
        }

        return;
    }

    int index = 0;

    while(index != -1)
    {
            if (stop_thread_)
            {
                emit (changeUrlLabel (""));
                return;
            }

            cs.searchAfter(httpData.getData(), "<a ",&index); //search for links

            while (lookForHref(httpData.getData(),index) && index!=-1)
                cs.searchAfter(httpData.getData(), "<a ",&index); //in case in tag 'a' haven't 'href'

            //found an url
            if (index!=-1)
            {
                getUrl(httpData.getData(),index, url); //get url
                QString return_url;

                buildUrl(url_root_, url, return_url);
                if (return_url == "") // if fail to build url
                {
                    log_.write(url  + "\n","ignore.txt");
                    continue;
                }

                if (!findUrlDB(return_url))
                {
                     log_.write(return_url, "log.txt");
                     QString url_tmp = return_url;

                     if (return_url.length()>2047)
                     {
                         qDebug()<<"Lenght > 2047 !!!";
                     }
                     else
                     {
                         insertUrlDB(return_url);
                     }

                     url_queue_.push(url_tmp);
                }
            }
    }
}

bool RSSSearchGUIThread::setUrlRoot(QString url)
{
    Http http;
    Search cs;

    QString query_part="";
    http.queryPartAndURL(url,query_part);
    int index = 0;
    cs.searchBefore(url, "www.", &index);

    if (index == 0) //remove 'www.'
    {
        url_root_="";
        for (int i=4; i<url.length(); i++)
        {
            url_root_+=url[i];
        }
    }
    else
    {
        url_root_ = url;
    }

    if (url_root_ == "")
    {
        return 0;
    }

    return 1;
}


//get url from html_source after index
void RSSSearchGUIThread::getUrl (const QString &html_source, int &index, QString &return_url)
{
    return_url ="";
    while(index< html_source.length() && html_source[index]!='\"') //vol
    {
        index++;
    }
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
        {
            return_url_tmp+=return_url[i];
        }
        return_url = return_url_tmp;
    }
}

//Build full url name
void RSSSearchGUIThread::buildUrl (const QString &url_root, const QString &url, QString &return_url)
{
    Search cs;
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
        {
            continue;
        }

        return_url+=url[i];
    }


    int ret  = 0, ret1 = 0;
    cs.searchBefore(return_url,url_root, &ret); //search for root_url
    cs.searchAfter(return_url,"://", &ret1); //search for protocol
    if (ret == -1 && ret1 == -1  && return_url.length()>0)
    {
        if (url_root[url_root.length()-1] == '/' && return_url[0]!='/')
        {
            return_url = url_root + return_url;
        }
        else if (url_root[url_root.length()-1] != '/' && return_url[0]!='/')
        {
            return_url = url_root + '/' + return_url;
        }
        else if (url_root[url_root.length()-1] == '/' && return_url[0]=='/')
        {
            QString return_url_tmp = return_url;
            return_url ="";
            for (int i=1; i<return_url_tmp.length(); i++) //without '/'
            {
                return_url+=return_url_tmp[i];
            }
            return_url = url_root + return_url;
        }
        else
        {
            return_url = url_root + return_url;
        }
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
    {
        fixProtocol(return_url);
    }
}

int RSSSearchGUIThread::fixProtocol(QString &url)
{
    Search cs;
    int index = 0;

    cs.searchBefore(url, "http://", &index);

    if (index == -1 || index == 0)
        return 0;

    QString url_tmp = "";
    for (int i = index; i<url.length(); i++)
        url_tmp += url[i];

    url = url_tmp;

    return 1;
}

int RSSSearchGUIThread::checkForRss(const QString &source, QString &title, int &version)
{
    Search cs;
    QString begin="<?xml";
    //Logger log;

    if (source.length()<4)
    {
        //log.write("CheckForRss funtion: source.length()<4!");
        return 1;
    }
    int i=0, j=0, r=0, f=0;
    cs.searchAfter(source, "<?xml", &i);
    cs.searchAfter(source, "<rss", &j);
    cs.searchAfter(source, "<rdf", &r);
    cs.searchAfter(source, "<feed", &f);

    if (i==0 || (j==-1 && r==-1 && f ==-1) || (j!=-1 && i>j) || (r!=-1 && i>r) || (f!=-1 && i>f))
        return 1;

    if (f!=-1 && j==-1 && r==-1)
        version = 2005;

    //get rss title
    i=0;
    cs.searchAfter(source, "<title>", &i);
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

int RSSSearchGUIThread::lookForHref(const QString &source, int &index)
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
        {
            return 0;
        }

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
    {
        index =-1;
    }

    index = old_index;
    return 1;
}

void RSSSearchGUIThread::addOrRemoveLastSymbolSlash(const QString &url, QString *new_url)
{
    if (url[url.length()-1]!='/')
    {
        *new_url = url + '/';
    }
    else //without '/'
    {
        for (int i=0; i<url.length()-1; i++)
        {
            *new_url+=url[i];
        }
    }
}

//i1 - index before root_url
//i - index after '://'
int RSSSearchGUIThread::checkForRootURL(const QString &url, int i, int i1)
{
    if (i==-1)
    {
        i=0;
    }
    while (i<url.length() && url[i]!='/')
    {
        i++;
    }
    if (i1 < i)
    {
        return 0;
    }
    return 1;
}

int RSSSearchGUIThread::insertUrlDB(const QString &url)//+
{
    return data_base_.insertIntoAllURLs(url);
}

int RSSSearchGUIThread::findUrlDB(const QString &url)
{
    return data_base_.selectURLFromAllURLs(url);
}

int RSSSearchGUIThread::deleteAllFrom_all_url_table() //delete all_url table
{
    return data_base_.deleteAllFromAllURL();
}

QString RSSSearchGUIThread::getEncodingFromRSS(const QString &content)
{
    Search cs;
    QString encoding="";
    int index1=0, index2=0;

    cs.searchAfter(content,"<?xml", &index1);

    if (index1 == -1)
    {
        return "";
    }

    cs.searchBefore(content, "?>", &index2);

    if (index2 == -1)
    {
        return "";
    }

    cs.searchAfter(content, "encoding=", &index1);

    if (index1 == -1 || index1>index2)
    {
        return "";
    }

    while (content[index1]!='\'' && content [index1]!='\"' && index1<index2)
    {
        index1++;
    }

    index1++;
    while (content[index1]!='\'' && content [index1]!='\"' && index1<index2)
    {
        encoding += content[index1++];
    }

    return encoding;
}



void RSSSearchGUIThread::setupConnections ()
{
    connect( this
            , SIGNAL(httpGetRequest(const QString &))
            , network_manager_.get()
            , SLOT(onHttpGetRequest(const QString &))
            , Qt::QueuedConnection);

    connect( network_manager_.get()
            , SIGNAL(httpRequestReceived(const HttpData &))
            , this
            , SLOT(onHttpRequestReceived(const HttpData &))
            , Qt::QueuedConnection);
}

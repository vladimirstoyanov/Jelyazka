/*
    http.cpp
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
#include "http.h"

Http::Http()
{
    url_option_ =0;
}
Http::~Http()
{
}

//ToDo: refactor this method
void Http::getRequest(const QString &urlParam)
{
    QTcpSocket socket;
    QString query_string="";
    QString url = urlParam;
    QString content = "";
    HttpData httpData;
    HttpRequestResultAnalyzer httpRequestResultAnalyzer;

    httpData.setUrl(urlParam);

    url_option_=1;
    checkAndChangeURL2(url);

    queryPartAndURL(url,query_string);
    if (query_string == "")
    {
        query_string += '/';
    }

    //ToDo: move this one in NetworkManager class
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        QNetworkProxy network_proxy;
        network_proxy.setHostName(Jelyazka::Settings::getProxyIpAddress());
        network_proxy.setPort(Jelyazka::Settings::getProxyPort().toInt());
        socket.setProxy(network_proxy);
    }

    socket.connectToHost(url,80,QIODevice::ReadWrite);
    if(!socket.waitForConnected())
    {
        socket.close();
        httpData.setIsResponseSuccessful(false);
        emit (httpRequestResult(httpData));
        return;
    }
    QString http_query = "GET " +query_string + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    QByteArray ba2;
    ba2 = http_query.toLocal8Bit();
    socket.write(ba2.data());

    QByteArray ba1;
    content ="";

    socket.waitForReadyRead();
    ba1=socket.readAll();
    content += ba1.data();

    QString response_num = "";
    float r_num = 0;
    int try_num = 0;
    int try_count = 10;

    httpRequestResultAnalyzer.checkResponse(content, response_num);

    if (response_num.length() == 3)
    {
        r_num = response_num.toFloat();
    }

    if (r_num>307) //trying to add or remove www (400 bad request)
    {
        addOrRemoveWWW(url);
    }

    while((r_num<200 || r_num>300) && try_num<try_count)
    {
        getCorrectURL(content, url);
        content="";
        socket.close();

        reconnect(url, content, socket);

        response_num = "";
        httpRequestResultAnalyzer.checkResponse(content, response_num);
        if (response_num.length() == 3)
        {
            r_num = response_num.toFloat();//return 0, if it cat't convert QString to float
        }

        if (r_num>307)
        {
            addOrRemoveWWW(url);
        }

        try_num++;
    }
    if (r_num!=200)
    {
        socket.close();
        emit(httpRequestResult(httpData));
        return;
    }

    httpData.setContentType(httpRequestResultAnalyzer.getContentType(content));
    if (ContentType::OTHER == httpData.getContentType())
    {
        socket.close();
        emit(httpRequestResult(httpData));
        return;
    }

    while(socket.waitForReadyRead())
    {
        ba1=socket.readAll();
        content += ba1.data();
    }
    socket.close();

    httpData.setData(content);
    httpData.setIsResponseSuccessful(true);
    emit(httpRequestResult(httpData));
}

/*
//http get query
//ToDo: refactor it
int Http::getRequest(const QString &urlParam, QString &content , int &type)
{
    QTcpSocket socket;
    QString query_string="";
    QString url = urlParam;

    url_option_=1;
    checkAndChangeURL2(url);

    queryPartAndURL(url,query_string);
    if (query_string == "")
    {
        query_string += '/';
    }

    //ToDo: test it
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        QNetworkProxy network_proxy;
        network_proxy.setHostName(Jelyazka::Settings::getProxyIpAddress());
        network_proxy.setPort(Jelyazka::Settings::getProxyPort().toInt());
        socket.setProxy(network_proxy);
    }

    socket.connectToHost(url,80,QIODevice::ReadWrite);
    if(!socket.waitForConnected())
    {
        socket.close();
        return 1;
    }
    QString http_query = "GET " +query_string + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    QByteArray ba2;
    ba2 = http_query.toLocal8Bit();
    socket.write(ba2.data());

    QByteArray ba1;
    content ="";

    socket.waitForReadyRead();
    ba1=socket.readAll();
    content += ba1.data();

    QString response_num = "";
    float r_num = 0;
    int try_num = 0;
    int try_count = 10;

    checkResponse(content, response_num);

    if (response_num.length() == 3)
    {
        r_num = response_num.toFloat();
    }

    if (r_num>307) //trying to add or remove www (400 bad request)
    {
        addOrRemoveWWW(url);
    }

    while((r_num<200 || r_num>300) && try_num<try_count)
    {
        getCorrectURL(content, url);
        content="";
        socket.close();

        reconnect(url, content, socket);

        response_num = "";
        checkResponse(content, response_num);
        if (response_num.length() == 3)
        {
            r_num = response_num.toFloat();//return 0, if it cat't convert QString to float
        }

        if (r_num>307)
        {
            addOrRemoveWWW(url);
        }

        try_num++;
    }
    if (r_num!=200)
    {
        socket.close();
        return 1;
    }

    type = isHTMLorXML(content);
    if (!type)
    {
        socket.close();
        return 1;
    }

    while(socket.waitForReadyRead())
    {
        ba1=socket.readAll();
        content += ba1.data();
    }
    socket.close();
    return 0;
}

//ToDo: refactor it
//http get query method with proxy argument
int Http::getRequest(const QString &urlParam, QString &content)
{
    QTcpSocket socket;
    QString query_string="";
    QString url = urlParam;

    url_option_=1;
    checkAndChangeURL2(url);

    queryPartAndURL(url,query_string);
    if (query_string == "")
    {
        query_string += '/';
    }


    //ToDo: test it
    if (Jelyazka::Settings::getIsProxyConnectionEnabled())
    {
        QNetworkProxy network_proxy;
        network_proxy.setHostName(Jelyazka::Settings::getProxyIpAddress());
        network_proxy.setPort(Jelyazka::Settings::getProxyPort().toInt());
        socket.setProxy(network_proxy);
    }

    socket.connectToHost(url,80,QIODevice::ReadWrite);
    if(!socket.waitForConnected())
    {
        socket.close();
        return 1;
    }
    QString http_query = "GET " +query_string + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    QByteArray ba2;
    ba2 = http_query.toLocal8Bit();
    socket.write(ba2.data());

    QByteArray ba1;
    content ="";

    //first text
    socket.waitForReadyRead();
    ba1=socket.readAll();
    content += ba1.data();

    QString response_num = "";
    float r_num = 0;
    int try_num = 0;
    int try_count = 5;

    checkResponse(content, response_num);

    if (response_num.length() == 3)
    {
        r_num = response_num.toFloat();
    }
    while((r_num<200 || r_num>300) && try_num<try_count)
    {
        getCorrectURL(content, url);
        content="";
        socket.close();
        reconnect(url, content, socket);
        response_num = "";
        r_num = 0;
        checkResponse(content, response_num);
        if (response_num.length() == 3)
        {
            r_num = response_num.toFloat();
        }
        if (r_num>307)
        {
            return 1;
        }
        try_num++;
    }

    while(socket.waitForReadyRead())
    {
        ba1=socket.readAll();
        content += ba1.data();
    }
    socket.close();
    return 0;
}
*/

int Http::reconnect(QString url, QString &content, QTcpSocket &socket)
{
    QString query_string="";
    content = "";
    queryPartAndURL(url,query_string);
    if (query_string == "")
    {
        query_string += '/';
    }
    socket.connectToHost(url,80,QIODevice::ReadWrite);
    if(!socket.waitForConnected(5000))
    {
        socket.close();
        return 1;
    }
    QString http_query = "GET " +query_string + " HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";
    QByteArray ba2;
    ba2 = http_query.toLocal8Bit();
    socket.write(ba2.data());

    QByteArray ba1;
    content ="";

    //first text
    socket.waitForReadyRead();
    ba1=socket.readAll();
    content += ba1.data();
    return 0;
}

void Http::queryPartAndURL(QString &url, QString &query_part)
{
    Search cs;
    QString tmp_url="";
    int i=0;
    cs.searchAfter(url,"://",&i);
    if (i==-1)
    {
        i=0;
    }
    for (; i<url.length(); i++)
    {
        if (url[i]=='/')
        {
            break;
        }
        tmp_url+=url[i];
    }
    for (;i<url.length(); i++)
    {
        query_part+=url[i];
    }

    url=tmp_url;
}

bool Http::checkInTheBeginning(const QString &url, const QString &http)
{
    int n = url.length();
    int n1 = http.length();

    for (int i=0; i<n; i++)
    {
        if (i==n1)
        {
            return 1;
        }

        if (http[i]!=url[i])
        {
            return 0;
        }
    }
    return 0;
}

//check the middle of url for substring
bool Http::checkInMiddle(const QString &url, const QString &substring, int begin_index) //0 - contain substring, 1- not contain
{

    int n = url.length();
    int n1 = substring.length();

    if (begin_index+n1 >= n) //if begin
    {
        return 1;
    }

    int j=0;
    for (; begin_index<n; begin_index++) //check if in the beginig have http://
    {
        if (j==n1)
        {
            return 0;
        }

        if (substring[j++]!=url[begin_index])
        {
            return 1;
        }
    }
    return 1;
}

void Http::checkAndChangeURL2(QString &url)
{
    int index=0;
    QString url_tmp = url;
    bool flag=false;
    url="";

    flag = checkForProtocol(url_tmp,index);
    flag = checkInMiddle(url_tmp, "www.",index);
    if (!flag)
    {
        index+=4;
    }

    for (; index<url_tmp.length(); index++)
    {
        url += url_tmp[index];
    }
}

bool Http::checkForProtocol(const QString &url, int &index_after_protocol, QString &protocol)
{
    protocol = "";
    index_after_protocol = 0;
    for (int i=0; i<url.length(); i++)
    {
        if (url[i]=='/')
        {
            if (i==0 || i+1>=url.length())
            {
                return 1;
            }
            if (url[i-1] != ':' || url[i+1] != '/')
            {
                return 1;
            }

            //set a protocol
            protocol = url.mid(0,i);
            index_after_protocol = i+2;
            return 0;
        }
    }
    return 1;
}

bool Http::checkForProtocol(const QString &url, QString &protocol)
{
    protocol = "";
    for (int i=0; i<url.length(); i++)
    {
        if (url[i]=='/')
        {
            if (i==0 || i+1>=url.length())
            {
                return 1;
            }
            if (url[i-1] != ':' || url[i+1] != '/')
            {
                return 1;
            }

            protocol = url.mid(0,i-1);
            return 0;
        }
    }
    return 1;
}

bool Http::checkForProtocol(const QString &url, int &index)
{
    index =0;
    for (int i=0; i<url.length(); i++)
    {
        if (url[i]=='/')
        {
            if (i==0 || i+1>=url.length())
            {
                return 1;
            }
            if (url[i-1] != ':' || url[i+1] != '/')
            {
                return 1;
            }

            index = i+2;

            return 0;
        }
    }
    return 1;
}

bool Http::checkForProtocol(const QString &url)
{
    for (int i=0; i<url.length(); i++)
    {
        if (url[i]=='/')
        {
            if (i==0 || i+1>=url.length())
            {
                return 1;
            }
            if (url[i-1] != ':' || url[i+1] != '/')
            {
                return 1;
            }
            return 0;
        }
    }
    return 1;
}

void Http::addSubStringAtBeginning(QString &url, const QString &substring)
{
    url = substring + url;
}

void Http::removeSubString(QString &url, const QString &substring)
{
    Search cs;
    QString newURL="";
    int index=0;
    int i;
    cs.searchBefore(url, substring, &index);

    for (i=0; i<index; i++)
    {
        newURL+=url[i];
    }
    index+=substring.length();
    i=0;
    for (i=index; i<url.length(); i++)
    {
        newURL+=url[i];
    }

    url = newURL;
}

void Http::changeUrl(QString &url, const int option)
{
    switch(option)
    {
        case 1:
        {
            url_option_ =1;
            checkAndChangeURL2(url);
            break;
        }
        case 2:
        {
            url_option_=2;
            addSubStringAtBeginning(url,"www.");
            break;
        }
        case 3:
        {
            url_option_=3;
            addSubStringAtBeginning(url,"http://");
            break;
        }
        case 4:
        {
            url_option_=4;
            removeSubString(url,"www.");
            break;
        }
        default:
        {
            url_option_ = 0;
            break;
        }
    }
}

void Http::getCorrectURL(const QString &content, QString &url)
{
    Search cs;
    int i=0;
    QString url_tmp = "";

    cs.searchAfter(content, "Location:",&i);

    if (i==-1)
    {
        return;
    }

    while (content[i]!='\r' && i<content.length())
    {
        if (content[i]==' ')
        {
            i++;
            continue;
        }
        url_tmp += content[i];
        i++;
    }
    url = url_tmp;
}

void Http::addOrRemoveWWW(QString &url)
{
    QString url_tmp = "";
    Search cs;
    int index = 0;

    cs.searchAfter(url, "://", &index);

    if (index==-1)
    {
        index = 0;
    }

    for (int i=0; i<index; i++) //add protocol
    {
        url_tmp+=url[i];
    }

    //remove "www."
    if (index+3<url.length())
    {
        if (url[index]=='w' && url[index+1]=='w' && url[index+2] =='w' && url[index+3]=='.')
        {
            for (int i=index+4; i<url.length(); i++) //add url without "www."
            {
                url_tmp+=url[i];
            }
            url = url_tmp;
            return;
        }
    }


    //add "www."
    url_tmp += "www.";
    for (int i=index; i<url.length(); i++)
    {
        url_tmp+=url[i];
    }

    url = url_tmp;
}

/*
    siteinterate.cpp
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
#include "siteinterate.h"

SiteInterate::SiteInterate()
{
}
SiteInterate::~SiteInterate()
{

}

void SiteInterate::InterateSite(QString url_addres, vector<QString>&result_urls)
{
    CSearch cs;
    QString url;
    QString html;
    QString url_root;
    Logger log;

    AllURLVariants(url_addres); //fill l_urlvariants vector

    l_url.push_back(url_addres);

    Net *n = new Net();
    int num = 0;
    vector<QString> result_urls_tmp;
    while (l_url.size()>0)
    {

        url = l_url[0];
        log.write("----------------------");
        log.write(url); //write current url to log file

        num++;
        int type =0;
        if (n->GetQuery3(url, html, type,url_root)) //if can't connect with url
        {
            log.write("Fail to connect to this site...");
            l_url.erase(l_url.begin());
            continue;
        }
        if (type == 2) //xml
             if (!CheckForRss(html)) //found rss
             {
                 result_urls_tmp.push_back(url);
                 log.write("==RSS==:" + url);
                 l_url.erase(l_url.begin());
                 continue;
             }

        log.writeHTMLSourceToFile("01.txt",html);
        int index = 0;

        while(index != -1)
        {

            cs.Search_After(&html, "<a ",&index); //search for links
            while (LookForHref(html,index) && index!=-1)
                cs.Search_After(&html, "<a ",&index); //in case in tag 'a' haven't 'href'


            if (index!=-1)
            {
                GetUrl(html,index, url); //get url
                log.write("Get url: " + url);
                QString return_url;
                BuildUrl(url_root, url, return_url);

                if (return_url == "") // if fail to build url
                    continue;

                url = return_url;

                /*
                int ret = CheckUrl(url,html);
                if (!ret) //found rss
                {
                    result_urls_tmp.push_back(url);
                    continue;
                }
                */
                //else {
                if (!CheckListForExistUrl(url)) //if url is not in vector list
                {
                    log.write("Adding to VECTOR LIST...");
                    l_url.push_back(url);
                    l_all_url.push_back(url);
                }
                //}
            }

        }
        l_url.erase(l_url.begin()); //delete first element from vector
    }
    result_urls.swap(result_urls_tmp);
    delete n;
}

int SiteInterate::CheckUrl (QString url, QString source)
{
    QString suffix="";
    int j=0;

    for (int i=url.length()-1; i>=0; i--)
    {
        if (j==4)
            break;
        j++;
        suffix += url[i];
    }

    //ako url-a e php-ski ?
    if (suffix == ".xml" || suffix == ".rss")
        return 0;
    return CheckForRss(source);
}

//get url from html_source after index
void SiteInterate::GetUrl (QString html_source, int &index, QString &return_url)
{
    return_url ="";
    while(html_source[index]!='\"')
        index++;
    index++;

    while(html_source[index]!='\"')
    {
        return_url+=html_source[index];
        index++;
    }
}

int SiteInterate::CheckListForExistUrl(QString url)
{
    for (int i=0; i<l_all_url.size(); i++) //l_url vector list with url's
        if (url==l_all_url[i])
            return -1;
    return 0;
}

//Build full url name
void SiteInterate::BuildUrl (QString url_root, QString url, QString &return_url)
{
    CSearch cs;
    return_url = "";

    for (int i=0; i<url.length(); i++)
    {
        if (int(url[i].toLatin1()) == 32) //if url has space then add %20
        {
            return_url+=return_url + "%20";
            continue;
        }
        return_url+=url[i];
    }

    int ret  = 0;

    cs.Search_After(&return_url,"://", &ret); //search for protocol

    if (ret == -1) //if it hasn't protocol (if it has part ot url, without root url
    {
        if (url_root[url_root.length()-1] == '/' && return_url[0]!='/')
            return_url = url_root + return_url;
        else if (url_root[url_root.length()-1] != '/' && return_url[0]!='/')
            return_url = url_root + '/' + return_url;
        else if (url_root[url_root.length()-1] == '/' && return_url[0]=='/')
        {
            QString return_url_tmp = return_url;
            return_url ="";
            for (int i=1; i<return_url_tmp.length(); i++) //without /
                return_url+=return_url_tmp[i];
            return_url = url_root + return_url;
        }
        else
            return_url = url_root + return_url;
        return;
    }

    if (CheckForRootURL(return_url, url_root)) //if url is from another web site
    {
        return_url = ""; //unvalide url
        return;
    }

    for (int i=0; i<l_url_variants.size(); i++) //url is the same with root_url
        if (l_url_variants[i] == return_url)
        {
            return_url =  "";
            return;
        }
}

void SiteInterate::AllURLVariants(QString &url)
{
    QString protocol="";
    QString new_url ="";
    Net net;
    if (net.checkForProtocol(url, protocol)) //if haven't protocol in url
    {
        url = "http://" + url;
        protocol = "http";
    }

    l_url_variants.push_back(url);
    l_all_url.push_back(url);
    AddOrRemoveLastSymbolSlash(url, new_url);
    l_url_variants.push_back(new_url);
    l_all_url.push_back(new_url);

    QString www = "www.";
    int n = protocol.length()+3;
    for (int i=n; i<url.length(); i++)
    {
        if (www.length() == i - n ) //it have www
        {
            //remove www.
            QString new_url ="";
            for (int j=0; j<url.length(); j++)
            {
                if (j>=i ||j<i-4)
                    new_url+=url[j];
            }
            l_url_variants.push_back(new_url);
            l_all_url.push_back(new_url);
            AddOrRemoveLastSymbolSlash(url, new_url);
            l_url_variants.push_back(new_url);
            l_all_url.push_back(new_url);
            return;
        }
        if (url[i]!=www[i-n]) // if haven't www
        {
            //add www.
            QString n_url = "";

            for (int j=0; j<url.length(); j++)
            {
                if (j==n+3)
                    n_url+=www;
                n_url+=url[j];
            }
            l_url_variants.push_back(n_url);
            l_all_url.push_back(n_url);
            AddOrRemoveLastSymbolSlash(n_url, new_url);
            l_url_variants.push_back(new_url);
            l_all_url.push_back(new_url);
        }
    }


}

/*
int  SiteInterate::CompaereTwoUrls (QString str, QString sub_str)
{
    if (str.length()<sub_str.length())
    for (int i = 0; i< str.length(); i++)
    {
        
    }
}

void SiteInterate::CheckAndChangeURL(QString &url)
{
    //end point = http://www.<url>
    QString t1 = "http://";
    QString t2 = "www.";
    bool l=0;
    for (int i=0; i<url.length(); i++)
    {
        if (t1.length() == i ) //sydyrja http://
            break;

        if (url[i]!=t1[i])
        {
            url = "http://" + url; 
            break;    
        }
    }

    for (int i=0; i<url.length(); i++)
    {
        if (t2.length() == i) //sydyrja www.
            break;
        if (url[i]!=t2[i])
            break;
    }

}
*/

//greshna funkciq, zashtoto v nachalot na source ima opisanie za zaqvkata (http 200 ok i t. n.)
int SiteInterate::CheckForRss(QString source)
{
    CSearch cs;
    QString begin="<?xml";

    if (source.length()<4)
        return 1;
    int i=0;
    cs.Search_After(&source, "<?xml", &i);
    if (i == -1) //not xml
        return 1;
    /*
    int i=0;
    for (i=0; i<begin.length(); i++) //check beggining for rss
        if (begin[i]!=source[i])
            return 1;
    i++;
    */

    int n = source.length();
    while(source[i]!='>' && i<n)
        i++;

    if (i>=n)
        return 1;

    while(source[i]!='<' && i<n)
        i++;

    if (i>=n)
        return 1;

    begin = "<rss version=\"";
    for (int j=0; j<begin.length(); j++)
    {
        QChar a = begin[j];
        QChar b = source[i];
        if (begin[j]!=source[i++])
            return 1;
    }

    QString version = "";
    while(source[i]!='\"' && i<n)
        version+=source[i++];


    return 0;
}

int SiteInterate::LookForHref(QString source, int &index)
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
        if (j==n1) //finded href before >
            return 0;
        QChar a1 = source[index];
        QChar a2 = label[j];
        if (source[index]!=label[j])
        {
            j=0;
            index++;
            continue;
        }
        j++;
        index++;
    }
    if (index == n) //if not found href= in source
        index =-1;

    index = old_index;
    return 1;
}

void SiteInterate::AddOrRemoveLastSymbolSlash(QString url, QString &new_url)
{
    new_url = url;
    if (url[url.length()-1]!='/')
        new_url += '/';
    else //remove /
    {

        for (int i=0; i<url.length()-1; i++)
            new_url+=url[i];
    }
}

//0 - it has root address
//1- it hasn't root address
int SiteInterate::CheckForRootURL(QString url, QString root_url)
{
    CSearch cs;
    int index=0;
    int n = url.length();
    int n1 = root_url.length()-1;
    int j=0;

    if (n==0 || n1==0)
        return 1;

    cs.Search_After(&url,"://",&index);

    if (index==-1)
        index = 0;

    while(url[index]!='/' && (index+n1)<n)
    {
        if (j==n1+1)
            return 0;
        if (url[index]!=root_url[j])
            j=0;
        j++;
        index++;
    }
    return 1;
}

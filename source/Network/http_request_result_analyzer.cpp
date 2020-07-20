/*
    http_request_result_analyzer.cpp
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
#include "http_request_result_analyzer.h"

HttpRequestResultAnalyzer::HttpRequestResultAnalyzer()
{
}
HttpRequestResultAnalyzer::~HttpRequestResultAnalyzer()
{
}

ContentType HttpRequestResultAnalyzer::getContentType(const QString &content)
{
    Search cs;
    int index=0, n = content.length();
    QString content_type="";
    cs.searchAfter(content, "Content-Type:", &index);

    if (index==-1 || index >= n)
    {
        return ContentType::OTHER;
    }

    while(content[index]==' ' && index<n) //ignore spaces
    {
        index++;
    }

    while(content[index]!=';' && content[index]!='\r' && index<n)
    {
        content_type+=content[index++];
    }

    if (content_type=="text/html")
    {
        return ContentType::HTML;
    }

    if (content_type == "text/xml"|| content_type=="text/rss+xml" || content_type == "application/rss+xml" || content_type == "application/xml")
    {
        return ContentType::XML;
    }

    return ContentType::OTHER;
}

bool HttpRequestResultAnalyzer::checkResponse(const QString &content, QString &response_num)
{
    int size_string = content.length();
    if (size_string<6) //Http/<num version>
    {
        return 1;
    }

    int i = 5;
    while (content[i]!= ' ') //after num version
    {
        i++;
        if (i>=size_string)
        {
            return 1;
        }
    }
    i++;
    if (i>=size_string)
    {
        return 1;
    }

    response_num=""; //response number of http response

    while (content[i]!=' ')
    {
        response_num+=content[i];
        i++;
        if (i>=size_string)
        {
            return 1;
        }
    }

    if (response_num!="200") //200 OK
    {
        return 1;
    }
    return 0;
}

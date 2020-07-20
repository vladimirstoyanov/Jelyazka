/*
    http_request_result_analyzer.h
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
#ifndef HTTP_REQUEST_RESULT_ANALYZER_H
#define HTTP_REQUEST_RESULT_ANALYZER_H


#include <QDebug>
#include <QDialog>
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QTextCodec>

#include "http_data.h"
#include "http_protocol.h"
#include "settings.h"
#include "search.h"

class HttpRequestResultAnalyzer
{
public:
    HttpRequestResultAnalyzer();
    virtual ~HttpRequestResultAnalyzer();


public:
    ContentType  getContentType(const QString &content);
    bool checkResponse(const QString &content, QString &response_num);
};

#endif // HTTP_REQUEST_RESULT_ANALYZER_H

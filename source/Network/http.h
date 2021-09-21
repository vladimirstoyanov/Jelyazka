/*
    http.h
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
#ifndef HTTP_H
#define HTTP_H

#include <iostream>

#include <QDebug>
#include <QDialog>
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QTextCodec>

#include "http_data.h"
#include "http_request_result_analyzer.h"
#include "http_protocol.h"
#include "settings.h"
#include "search.h"



class Http : public IHttpProtocol
{
        Q_OBJECT
public:
    Http();
    virtual ~Http();

    void addSubStringAtBeginning(QString &url, const QString &substring);
    void addOrRemoveWWW(QString &url); //ToDo: rename this funtion
    void changeUrl(QString &url, const int option);
    void checkAndChangeURL2(QString &url); //ToDO: rename this function
    void convertURLToFileName(char *url, char **filename);
    void getCorrectURL(const QString &content, QString &url);
    void queryPartAndURL(QString &url, QString &query_part);
    void removeSubString(QString &url, const QString &substring);

    void getRequest(const QString &url) override;
    int  reconnect(QString url, QString &content, QTcpSocket &socket);
    bool checkInTheBeginning(const QString &url, const QString &http);
    bool checkForProtocol(const QString &url);
    bool checkForProtocol(const QString &url, QString &protocol);
    bool checkForProtocol(const QString &url, int &index);
    bool checkForProtocol(const QString &url, int &index, QString &protocol);
    bool checkInMiddle(const QString &url, const QString &substring, int begin_index);

signals:
    void httpRequestResult (const HttpData httpData);

private:
    int url_option_;
};

#endif // HTTP_H

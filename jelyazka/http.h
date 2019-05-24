/*
    net.h
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
#ifndef HTTP_H
#define HTTP_H

#include <iostream>

#include <QDebug>
#include <QDialog>
#include <QNetworkProxy>
#include <QTcpSocket>
#include <QTextCodec>

#include "rssthread.h"
#include "search.h"

class HTTP
{
public:
    HTTP();
    virtual ~HTTP();

    void addSubStringAtBeginning(QString &url, QString substring);
    void addOrRemoveWWW(QString &url); //ToDo: rename this funtion
    void changeUrl(QString &url, int option);
    void checkAndChangeURL2(QString &url); //ToDO: rename this function
    void convertURLToFileName(char *url, char **filename);
    void getCorrectURL(QString content, QString &url);
    void queryPartAndURL(QString &url, QString &query_part);
    void removeSubString(QString &url, QString substring);

public:
    int getQuery(QString url, QString &content, QNetworkProxy *network_proxy=NULL);
    int getQuery(QString url, QString &content, int &type);
    int isHTMLorXML(QString content);
    int reconnect(QString url, QString &content, QTcpSocket &socket);
    bool checkInTheBeginning(QString url, QString http);
    bool checkForProtocol(QString url);
    bool checkForProtocol(QString url, QString &protocol);
    bool checkForProtocol(QString url, int &index);
    bool checkForProtocol(QString url, int &index, QString &protocol);
    bool checkInMiddle(QString url, QString substring, int begin_index);
    bool checkResponse(QString content, QString &response_num);

private:
    int url_option_;
};

#endif // HTTP_H

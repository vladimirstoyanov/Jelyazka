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

#include <QDialog>
#include <iostream>
#include <QTcpSocket>
#include <QTextCodec>
#include <QDebug>
#include <QNetworkProxy>
#include "sitestruct.h"
#include "search.h"

class HTTP
{
public:
    HTTP();
    ~HTTP();
    int getQuery(QString url, QString &content, QNetworkProxy *network_proxy=NULL);
    int getQuery(QString url, QString &content, int &type);
    void convertURLToFileName(char *url, char **filename);
    void queryPartAndURL(QString &url, QString &query_part);
    void checkAndChangeURL2(QString &url);
    bool checkInTheBeginning(QString url, QString http);
    bool checkForProtocol(QString url);
    bool checkForProtocol(QString url, QString &protocol);
    bool checkForProtocol(QString url, int &index);
    bool checkForProtocol(QString url, int &index, QString &protocol);
    bool checkInMiddle(QString url, QString substring, int begin_index);
    bool checkResponse(QString content, QString &response_num);

    void addSubStringAtBeginning(QString &url, QString substring);
    void removeSubString(QString &url, QString substring);
    void ChangeUrl(QString &url, int option);
    int reconnect(QString url, QString &content, QTcpSocket &socket);
    int isHTMLorXML(QString content);
    void getCorrectURL(QString content, QString &url);

    void addOrRemoveWWW(QString &url);
private:
    int url_option;
};

#endif // HTTP_H

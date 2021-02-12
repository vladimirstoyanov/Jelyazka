/*
    network_manager.cpp
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
#include "network_manager.h"

NetworkManager::NetworkManager ():
    http (std::make_shared<Http> ()),
    https (std::make_shared<Https> ())
{
    setupConnections();
}

NetworkManager::~NetworkManager()
{
}
void NetworkManager::onHttpGetRequest(const QString &url)
{
    qDebug()<<__PRETTY_FUNCTION__;
    if (https->isHttpsProtocol(url))
    {
        qDebug()<<__PRETTY_FUNCTION__<<": https";
        https->getRequest(url);
    }
    else
    {
        qDebug()<<__PRETTY_FUNCTION__<<": http";
        http->getRequest(url);
    }
}
/*
void NetworkManager::getHttpRequest (const QString &url)
{
    qDebug()<<__PRETTY_FUNCTION__;
    if (https->isHttpsProtocol(url))
    {
        qDebug()<<__PRETTY_FUNCTION__<<": https";
        https->getRequest(url);
    }
    else
    {
        qDebug()<<__PRETTY_FUNCTION__<<": http";
        http->getRequest(url);
    }
}
*/

//Slot: onHttpRequestResult
void NetworkManager::onHttpRequestResult (const HttpData &httpData)
{
    qDebug()<<__PRETTY_FUNCTION__;
    httpRequestReceived(httpData);
}

void NetworkManager::setupConnections()
{
    qDebug()<<__PRETTY_FUNCTION__;
    connect( http.get()
            , SIGNAL(httpRequestResult(const HttpData &))
            , this
            , SLOT(onHttpRequestResult(const HttpData &))
            , Qt::QueuedConnection);

    connect( https.get()
            , SIGNAL(httpsRequestResult(const HttpData &))
            , this
            , SLOT(onHttpRequestResult(const HttpData &))
            , Qt::QueuedConnection);
}

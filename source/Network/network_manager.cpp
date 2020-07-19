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
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::getHttpRequest (const QString &url)
{
    if (https->checkIsProtolHttps(url))
    {
        https->getRequest(url);
    }
    else
    {
        http->getRequest(url);
    }
}

//Slot: onHttpRequestResult
void NetworkManager::onHttpRequestResult (const HttpData httpData)
{

}

void NetworkManager::setupConnections()
{

}

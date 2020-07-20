/*
    network_manager.h
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
#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <QObject>
#include <QString>

#include <memory>

#include "http.h"
#include "http_data.h"
#include "https.h"

class NetworkManager: public QObject
{
    Q_OBJECT
public:
    NetworkManager ();
    virtual ~NetworkManager();

    //void getHttpRequest (const QString &url);
public slots:
    void onHttpRequestResult (const HttpData httpData);
    void onHttpGetRequest       (const QString &);
signals:
    void httpRequestReceived (const HttpData httpData);
private:
    void setupConnections();
private:
    std::shared_ptr<Http> http;
    std::shared_ptr<Https> https;
};

#endif // NETWORK_MANAGER_H

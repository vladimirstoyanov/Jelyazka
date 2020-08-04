/*
    http_protocol.h
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

#ifndef JELYAZKA_HTTP_PROTOCOL_H
#define JELYAZKA_HTTP_PROTOCOL_H

#include <QObject>
#include <QString>

class IHttpProtocol: public QObject
{
        Q_OBJECT

public:
    IHttpProtocol () = default;
    virtual ~IHttpProtocol () = default;
    virtual void getRequest (const QString &url) = 0;
};

#endif // JELYAZKA_HTTP_PROTOCOL_H

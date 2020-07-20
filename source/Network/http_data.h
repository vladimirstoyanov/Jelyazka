/*
    http_data.h
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

#ifndef JELYAZKA_HTTP_DATA_H
#define JELYAZKA_HTTP_DATA_H

#include <QString>

enum ContentType
{
    XML,
    HTML,
    OTHER
};

class HttpData
{
public:
    HttpData ();
    virtual ~HttpData ();

    QString getData () const
    {
        return this->data_;
    }

    QString getUrl () const
    {
        return this->url_;
    }

    bool isResponseSuccessful () const
    {
        return this->is_response_successful_;
    }

    ContentType getContentType () const
    {
        return this->content_type_;
    }

    void setData (const QString &data)
    {
        this->data_ = data;
    }

    void setContentType(const ContentType content_type)
    {
        this->content_type_ = content_type;
    }

    void setIsResponseSuccessful (const bool is_response_successful)
    {
        this->is_response_successful_ = is_response_successful;
    }

    void setUrl (const QString &url)
    {
        this->url_ = url;
    }

private:
    QString data_;
    ContentType content_type_;
    bool is_response_successful_;
    QString url_;
};

#endif // JELYAZKA_HTTP_DATA_H

/*
    https.cpp
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
#include "https.h"

Https::Https():
    manager_ (std::make_shared<QNetworkAccessManager> ()),
    https_prefix_name_("https")
{
}

Https::~Https()
{
}

void Https::getRequest(const QString &url)
{
    QNetworkRequest request;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ServerHeader, "application/json");

    connect(manager_.get(),
            SIGNAL(finished(QNetworkReply*)), this,
            SLOT(replyFinished(QNetworkReply*)));

    manager_->get(request);
}

void Https::replyFinished(QNetworkReply* reply)
{
    HttpData httpData;
    HttpRequestResultAnalyzer httpRequestResultAnalyzer;
    QString response_code = "";
    httpData.setData(reply->readAll());
    httpRequestResultAnalyzer.checkResponse(httpData.getData(),response_code);

    if (response_code == "200")
    {
        httpData.setIsResponseSuccessful(true);
    }


    ContentType contentType = httpRequestResultAnalyzer.getContentType(httpData.getData());
    httpData.setContentType(contentType);

    emit(httpRequestResult(httpData));
}


bool Https::checkIsProtolHttps(const QString &url)
{
    bool result = false;
    QString prefix = url.mid(0,https_prefix_name_.size());
    if (prefix == https_prefix_name_)
    {
        result = true;
    }
    return result;
}

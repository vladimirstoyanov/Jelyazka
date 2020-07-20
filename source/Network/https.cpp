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
    qDebug()<<__PRETTY_FUNCTION__;

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config_.setProtocol(QSsl::TlsV1_2);
    request_.setSslConfiguration(config_);

    setupConnections();
}

Https::~Https()
{
}

void Https::setupConnections ()
{
    connect(manager_.get(),
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));

    connect(manager_.get(),
            SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
            this,
            SLOT(onAuthenticationRequired(QNetworkReply *, QAuthenticator *)));

    connect(manager_.get(),
            SIGNAL(encrypted(QNetworkReply *)),
            this,
            SLOT(onEncrypted(QNetworkReply *)));

    connect(manager_.get(),
            SIGNAL(preSharedKeyAuthenticationRequired(QNetworkReply *, QSslPreSharedKeyAuthenticator *)),
            this,
            SLOT(onPreSharedKeyAuthenticationRequired(QNetworkReply *, QSslPreSharedKeyAuthenticator *)));

    connect(manager_.get(),
            SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)),
            this,
            SLOT(onProxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));

    connect(manager_.get(),
            SIGNAL(sslErrors(QNetworkReply *, const QList<QSslError> &)),
            this,
            SLOT(onSslErrors(QNetworkReply *, const QList<QSslError> &)));
}
void Https::getRequest(const QString &url)
{
    qDebug()<<__PRETTY_FUNCTION__;

    request_.setUrl(QUrl(url));
    request_.setHeader(QNetworkRequest::ServerHeader, "application/json");

    manager_->get(request_);
}

void Https::replyFinished(QNetworkReply* reply)
{
    qDebug()<<__PRETTY_FUNCTION__;

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

    emit(httpsRequestResult(httpData));
}


bool Https::isHttpsProtocol(const QString &url)
{
    bool result = false;
    QString prefix = url.mid(0,https_prefix_name_.size());
    if (prefix == https_prefix_name_)
    {
        result = true;
    }
    return result;
}

void Https::onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qDebug()<<__PRETTY_FUNCTION__;
}
void Https::onEncrypted(QNetworkReply *reply)
{
    qDebug()<<__PRETTY_FUNCTION__;
}
void Https::onPreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug()<<__PRETTY_FUNCTION__;
}
void Https::onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<<__PRETTY_FUNCTION__;
}
void Https::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug()<<__PRETTY_FUNCTION__;
}

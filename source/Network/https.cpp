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

    QNetworkReply * reply = manager_->get(request_);


    connect(reply, &QIODevice::readyRead, this, &Https::onReadyRead);
    connect(reply, &QNetworkReply::errorOccurred,
            this, &Https::onError);
    connect(reply, &QNetworkReply::sslErrors,
            this, &Https::onSslErrorsNetworkReply);

}

void Https::replyFinished(QNetworkReply* reply)
{
    qDebug()<<__PRETTY_FUNCTION__;

    HttpData httpData;
    HttpRequestResultAnalyzer httpRequestResultAnalyzer;
    QString response_code = "";
    httpData.setData(reply->readAll());
    httpData.setUrl(reply->url().toString());
    httpRequestResultAnalyzer.checkResponse(httpData.getData(),response_code);

    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
    if ( statusCode.isValid() )
    {
        int status = statusCode.toInt();

        if ( status != 200 )
        {
            QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
            qDebug()<<__PRETTY_FUNCTION__<<", failed with reason: "<<reason;
        }
        else
        {
            qDebug()<<__PRETTY_FUNCTION__<<", reposnse is successful";
            httpData.setIsResponseSuccessful(true);
        }
    }


    QVariant contentMimeType = reply->header(QNetworkRequest::ContentTypeHeader);
    QString contentTypeStr = "Content-Type:" + QVariant(contentMimeType).toString();
    qDebug() <<"Content type"<< contentTypeStr;

    ContentType contentType = httpRequestResultAnalyzer.getContentType(contentTypeStr);
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
    qDebug()<<__PRETTY_FUNCTION__<<reply<<", "<<authenticator;
}
void Https::onEncrypted(QNetworkReply *reply)
{
    qDebug()<<__PRETTY_FUNCTION__<<reply;
}
void Https::onPreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug()<<__PRETTY_FUNCTION__<<reply<<", "<<authenticator;
}
void Https::onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<<__PRETTY_FUNCTION__<<proxy<<", "<<authenticator;
}
void Https::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    qDebug()<<__PRETTY_FUNCTION__<<reply<<", "<<errors;
}

void Https::onReadyRead()
{
    qDebug()<<__PRETTY_FUNCTION__;
}

void Https::onError(QNetworkReply::NetworkError code)
{
    qDebug()<<__PRETTY_FUNCTION__<<": code: "<<code;

}

void Https::onSslErrorsNetworkReply(const QList<QSslError> &errors)
{
    qDebug()<<__PRETTY_FUNCTION__<<errors;
}

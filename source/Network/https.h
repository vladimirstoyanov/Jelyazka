/*
    https.h
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

#ifndef JELYAZKA_HTTPS_H
#define JELYAZKA_HTTPS_H

#include <QCoreApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtDebug>

#include <memory>

#include "http_data.h"
#include "http_request_result_analyzer.h"
#include "http_protocol.h"

using namespace std;

class Https: public IHttpProtocol
{
    Q_OBJECT
public:
    Https ();
    virtual ~Https ();
    bool isHttpsProtocol(const QString &url);
    void getRequest (const QString &url);
    void postRequest (const QString &) {}
public slots:
    void replyFinished(QNetworkReply* reply);
    void onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void onEncrypted(QNetworkReply *reply);
    void onPreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);


private:
    void setupConnections();
private:
    QSslConfiguration config_;
    std::shared_ptr<QNetworkAccessManager> manager_;
    QString https_prefix_name_;
    QNetworkRequest request_;

signals:
    void httpsRequestResult (const HttpData httpData);
};

#endif // HTTPSGETCUSTOM_H

#include "https.h"

Https::Https():
    manager_ (std::make_shared<QNetworkAccessManager> ())
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
    qDebug() << reply->readAll();
}


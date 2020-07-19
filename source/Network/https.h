#ifndef JELYAZKA_HTTPS_H
#define JELYAZKA_HTTPS_H

#include <QCoreApplication>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtDebug>

#include <memory>

using namespace std;

class Https: public QObject
{
    Q_OBJECT
public:
    Https ();
    virtual ~Https ();
    void getRequest (const QString &url);
public slots:
    void replyFinished(QNetworkReply* reply);
private:
    std::shared_ptr<QNetworkAccessManager> manager_;
};

#endif // HTTPSGETCUSTOM_H

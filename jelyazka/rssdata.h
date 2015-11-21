#ifndef RSSDATA_H
#define RSSDATA_H

#include <QString>
#include <QList>
#include <limits.h>
#include "rssarticle.h"

class RSSData: public RSSArticle
{
public:
    RSSData();

    //get
    QString getType ();
    QString getSiteName();
    QString getURL();
    QString getEncoding();
    QString getVersion();
    bool getIsRead();
    bool getIsLoaded();
    size_t getArticlesSize();
    RSSArticle articleAt(unsigned int index);
    void eraseArticleAt(unsigned int index);
    void articlesPushFront(RSSArticle ar);
    void articlesPushBack(RSSArticle ar);

    //set
    void setType(QString type);
    void setSiteName(QString site_name);
    void setURL(QString url);
    void setEncoding(QString enconding);
    void setVersion(QString version);
    void setIsRead(bool isRead);
    void setIsLoaded(bool isLoaded);

private:
    QString type;
    QString site_name;
    QString url;
    QString encoding;
    QString version;
    bool isRead;
    bool isLoaded;
    //boost::ptr_list<article> articles; //new
    QList<RSSArticle> articles;

};

#endif // RSSDATA_H

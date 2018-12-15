#ifndef RSSDATA_H
#define RSSDATA_H

#include <limits.h>

#include <QList>
#include <QString>

#include "rssarticle.h"

class RSSData: public RSSArticle
{
public:
    RSSData();

    void articlesPushFront(RSSArticle rss_article);
    void articlesPushBack(RSSArticle rss_article);
    void eraseArticleAt(unsigned int index);
    void setEncoding(QString enconding);
    void setIsLoaded(bool isLoaded);
    void setIsRead(bool isRead);
    void setSiteName(QString site_name);
    void setType(QString type);
    void setURL(QString url);
    void setVersion(QString version);

public:
    bool getIsLoaded();
    bool getIsMarkedForRemove();
    bool getIsRead();
    size_t getArticlesSize();
    QString getEncoding();
    QString getSiteName();
    QString getType ();
    QString getURL();
    QString getVersion();
    RSSArticle articleAt(unsigned int index);

private:
    QString type_;
    QString site_name_;
    QString url_;
    QString encoding_;
    QString version_;
    bool is_read_;
    bool is_loaded_;
    //boost::ptr_list<article> articles; //new
    QList<RSSArticle> rss_article_list_;
};

#endif // RSSDATA_H

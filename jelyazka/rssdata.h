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
    bool getIsMarkedForRemove();
    size_t getArticlesSize();
    RSSArticle articleAt(unsigned int index);
    void eraseArticleAt(unsigned int index);
    void articlesPushFront(RSSArticle rss_article);
    void articlesPushBack(RSSArticle rss_article);

    //set
    void setType(QString type);
    void setSiteName(QString site_name);
    void setURL(QString url);
    void setEncoding(QString enconding);
    void setVersion(QString version);
    void setIsRead(bool isRead);
    void setIsLoaded(bool isLoaded);

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

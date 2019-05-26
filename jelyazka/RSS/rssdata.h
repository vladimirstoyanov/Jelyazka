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

    void articlesPushFront(const RSSArticle rss_article);
    void articlesPushBack(const RSSArticle rss_article);
    void eraseArticleAt(unsigned int index);
    void setEncoding(const QString &enconding);
    void setSiteName(const QString &site_name);
    void setType(const QString &type);
    void setURL(const QString &url);
    void setVersion(const QString &version);

public:
    size_t getArticlesSize();
    QString getEncoding () const;
    QString getSiteName() const;
    QString getType () const;
    QString getURL() const;
    QString getVersion() const;
    RSSArticle articleAt(unsigned int index);

private:
    QString type_;
    QString site_name_;
    QString url_;
    QString encoding_;
    QString version_;
    QList<RSSArticle> rss_article_list_;
};

#endif // RSSDATA_H

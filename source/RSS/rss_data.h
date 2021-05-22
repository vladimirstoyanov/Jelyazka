#ifndef RSSDATA_H
#define RSSDATA_H

#include <limits.h>

#include <QList>
#include <QString>

#include "rss_article.h"


class RSSData: public RSSArticle
{
public:
    RSSData();
    virtual ~RSSData () = default;

    void        articlesPushFront(const RSSArticle rss_article);
    void        articlesPushBack(const RSSArticle rss_article);
    void        eraseArticleAt(unsigned int index);
    void        setEncoding(const QString &enconding);
    void        setSiteName(const QString &site_name);
    void        setType(const QString &type);
    void        setURL(const QString &url);
    void        setVersion(const QString &version);

public:
    size_t      getArticlesSize() const;
    QString     getEncoding () const;
    QString     getSiteName() const;
    QString     getType () const;
    QString     getURL() const;
    QString     getVersion() const;
    RSSArticle  articleAt(unsigned int index) const;

private:
    QString           encoding_;
    QList<RSSArticle> rss_articles_;
    QString           site_name_;
    QString           type_;
    QString           url_;
    QString           version_;


};

#endif // RSSDATA_H

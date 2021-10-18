#ifndef JELYAZKA_RSSDATA_H
#define JELYAZKA_RSSDATA_H

#include <limits.h>

#include <QList>
#include <QString>


#include "rss_article.h"



class RSSData: public RSSArticle
{
public:
    RSSData();
    RSSData (const QString &name
             , const QString &url
             , const QString &encoding
             , const int version);

    virtual ~RSSData () = default;

    void        articlesPushFront(const RSSArticle rss_article);
    void        articlesPushBack(const RSSArticle rss_article);
    void        eraseArticleAt(unsigned int index);

    //ToDo: remove setters
    void        setEncoding(const QString &enconding);
    void        setSiteName(const QString &site_name);
    void        setURL(const QString &url);
    void        setVersion(const QString &version);


public:
    size_t      getArticlesSize() const;
    QString     getEncoding () const;
    QString     getSiteName() const;
    QString     getURL() const;
    QString     getVersion() const;
    RSSArticle  articleAt(unsigned int index) const;

private:
    QString           encoding_;
    QList<RSSArticle> rss_articles_;
    QString           site_name_;
    QString           url_;
    QString           version_;
};

#endif // JELYAZKA_RSSDATA_H

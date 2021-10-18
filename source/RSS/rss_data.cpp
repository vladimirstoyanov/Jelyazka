#include "rss_data.h"

RSSData::RSSData():
    encoding_ ("")
    , site_name_ ("")
    , url_ ("")
    , version_ ("")
{

}

RSSData::RSSData (const QString &name
                  , const QString &url
                  , const QString &encoding
                  , const int version):
    encoding_(encoding),
    site_name_(name),
    url_ (url),
    version_(version==0?"":"2005")
{
}


QString RSSData::getSiteName() const
{
    return site_name_;
}

QString RSSData::getURL() const
{
    return url_;
}

QString RSSData::getEncoding() const
{
    return encoding_;
}

QString RSSData::getVersion() const
{
    return version_;
}

size_t RSSData::getArticlesSize() const
{
    return rss_articles_.size();
}

RSSArticle RSSData::articleAt(unsigned int index) const
{
    RSSArticle default_value;
    if (index >= rss_articles_.size())
    {
        return default_value;
    }
    return rss_articles_[index];
}

void RSSData::eraseArticleAt(unsigned int index)
{
    rss_articles_.erase(rss_articles_.begin() + index);
}

void RSSData::articlesPushFront(const RSSArticle rss_article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(rss_article);
        return;
    }

    rss_articles_.push_front(rss_article);
}

void RSSData::articlesPushBack(const RSSArticle rss_article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(rss_article);
        return;
    }

    rss_articles_.push_back(rss_article);
}

void RSSData::setSiteName(const QString &site_name)
{
    site_name_ = site_name;
}

void RSSData::setURL(const QString &url)
{
    url_ = url;
}

void RSSData::setEncoding(const QString &enconding)
{
    encoding_ = enconding;
}

void RSSData::setVersion(const QString &version_tmp)
{
    version_ = version_tmp;
}


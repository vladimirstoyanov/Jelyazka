#include "rss_data.h"

RSSData::RSSData():
    current_index_rss_articles_ (0)
    , encoding_ ("")
    , site_name_ ("")
    , type_ ("")
    , url_ ("")
    , version_ ("")
{

}


//get
QString RSSData::getType () const
{
    return type_;
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

size_t RSSData::getArticlesSize()
{
    return rss_articles_.size();
}

RSSArticle RSSData::articleAt(unsigned int index)
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

//set
void RSSData::setType(const QString &type)
{
    type_ = type;
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


RSSArticle  RSSData::getCurrentArticle ()
{
    RSSArticle result;
    if (current_index_rss_articles_<rss_articles_.size())
    {
        return rss_articles_[current_index_rss_articles_];
    }
    return result; //RSSArticle class with empty values
}
RSSArticle  RSSData::getNextArticle ()
{
    RSSArticle result;
    if ((current_index_rss_articles_+1)<rss_articles_.size())
    {
        ++current_index_rss_articles_;
        return rss_articles_[current_index_rss_articles_];
    }

    return getCurrentArticle();
}

RSSArticle  RSSData::getPreviousArticle ()
{
    RSSArticle result;

    if ((current_index_rss_articles_-1)>-1)
    {
        --current_index_rss_articles_;
    }

    return getCurrentArticle();
}

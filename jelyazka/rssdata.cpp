#include "rssdata.h"

RSSData::RSSData()
{

}


//get
QString RSSData::getType ()
{
    return type_;
}

QString RSSData::getSiteName()
{
    return site_name_;
}

QString RSSData::getURL()
{
    return url_;
}

QString RSSData::getEncoding()
{
    return encoding_;
}

QString RSSData::getVersion()
{
    return version_;
}

bool RSSData::getIsRead()
{
    return is_read_;
}

bool RSSData::getIsLoaded()
{
    return is_loaded_;
}

size_t RSSData::getArticlesSize()
{
    return rss_article_list_.size();
}

RSSArticle RSSData::articleAt(unsigned int index)
{
    return rss_article_list_[index];
}

void RSSData::eraseArticleAt(unsigned int index)
{
    rss_article_list_.erase(rss_article_list_.begin() + index);
}

void RSSData::articlesPushFront(RSSArticle rss_article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(rss_article);
        return;
    }

    rss_article_list_.push_front(rss_article);
}

void RSSData::articlesPushBack(RSSArticle rss_article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(rss_article);
        return;
    }

    rss_article_list_.push_back(rss_article);
}

//set
void RSSData::setType(QString type)
{
    type_ = type;
}

void RSSData::setSiteName(QString site_name)
{
    site_name_ = site_name;
}

void RSSData::setURL(QString url)
{
    url_ = url;
}

void RSSData::setEncoding(QString enconding)
{
    encoding_ = enconding;
}

void RSSData::setVersion(QString version_tmp)
{
    version_ = version_tmp;
}

void RSSData::setIsRead(bool is_read)
{
    is_read_ = is_read;
}

void RSSData::setIsLoaded(bool is_loaded)
{
    is_loaded_ = is_loaded;
}

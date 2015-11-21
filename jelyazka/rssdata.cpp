#include "rssdata.h"

RSSData::RSSData()
{

}


//get
QString RSSData::getType ()
{
    return type;
}

QString RSSData::getSiteName()
{
    return site_name;
}

QString RSSData::getURL()
{
    return url;
}

QString RSSData::getEncoding()
{
    return encoding;
}

QString RSSData::getVersion()
{
    return version;
}

bool RSSData::getIsRead()
{
    return isRead;
}

bool RSSData::getIsLoaded()
{
    return isLoaded;
}

size_t RSSData::getArticlesSize()
{
    return articles.size();
}

RSSArticle RSSData::articleAt(unsigned int index)
{
    return articles[index];
}

void RSSData::eraseArticleAt(unsigned int index)
{
    articles.erase(articles.begin() + index);
}

void RSSData::articlesPushFront(RSSArticle article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(article);
        return;
    }

    articles.push_front(article);
}

void RSSData::articlesPushBack(RSSArticle article)
{
    if (INT_MAX <= getArticlesSize()) //prevent int overflow
    {
        eraseArticleAt(getArticlesSize()-1);
        articlesPushFront(article);
        return;
    }

    articles.push_back(article);
}

//set
void RSSData::setType(QString type_tmp)
{
    type = type_tmp;
}

void RSSData::setSiteName(QString site_name_tmp)
{
    site_name = site_name_tmp;
}

void RSSData::setURL(QString url_tmp)
{
    url = url_tmp;
}

void RSSData::setEncoding(QString enconding_tmp)
{
    encoding = enconding_tmp;
}

void RSSData::setVersion(QString version_tmp)
{
    version = version_tmp;
}

void RSSData::setIsRead(bool isRead_tmp)
{
    isRead = isRead_tmp;
}

void RSSData::setIsLoaded(bool isLoaded_tmp)
{
    isLoaded = isLoaded_tmp;
}

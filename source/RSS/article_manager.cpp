#include "article_manager.h"

ArticleManager::ArticleManager(const RSSData &rss_data):
    current_index_rss_articles_(0),
    rss_data_ (rss_data)
{

}

RSSArticle ArticleManager::getNextRssArticle ()
{
    if ((current_index_rss_articles_+1)<rss_data_.getArticlesSize())
    {
        ++current_index_rss_articles_;
        return rss_data_.articleAt(current_index_rss_articles_);
    }

    return getCurrentRssArticle();
}

RSSArticle ArticleManager::getPreviousRssArticle ()
{
    if ((current_index_rss_articles_-1)>-1)
    {
        --current_index_rss_articles_;
    }

    return getCurrentRssArticle();
}

RSSArticle ArticleManager::getCurrentRssArticle ()
{
    RSSArticle result;
    if (current_index_rss_articles_<rss_data_.getArticlesSize())
    {
        return rss_data_.articleAt(current_index_rss_articles_);
    }
    return result;
}

void  ArticleManager::setRssData (const RSSData &rss_data)
{
    rss_data_ = rss_data;
    current_index_rss_articles_ = 0;
}

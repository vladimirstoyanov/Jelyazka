#include "article_manager.h"

ArticleManager::ArticleManager(const RSSData &rss_data):
    current_index_rss_articles_(0),
    rss_data_ (rss_data)
{
}

bool ArticleManager::isArticleContainsFilters (const RSSArticle & article)
{
    Search search;
    for (unsigned int i=0; i<filters_.size(); ++i)
    {
        //check the title
        int index = 0;
        search.searchAfter(article.getTitle(), filters_[i], &index);
        if (index != -1)
        {
            return true;
        }

        //check the article
        index = 0;
        search.searchAfter(article.getText(), filters_[i], &index);
        if (index != -1)
        {
            return true;
        }
    }
    return false;
}

void ArticleManager::filterArticles ()
{
    for (size_t i=0; i<rss_data_.getArticlesSize(); ++i)
    {
        if (isArticleContainsFilters(rss_data_.articleAt(i)))
        {
            filtered_articles_.push_back(rss_data_.articleAt(i));
        }
    }
}

RSSArticle ArticleManager::getNextRssArticle ()
{
    if (Jelyazka::Settings::getIsFilteringEnabled()
       && (current_index_rss_articles_+1)<filtered_articles_.size())
    {
        ++current_index_rss_articles_;
        return filtered_articles_[current_index_rss_articles_];
    }
    else if (!Jelyazka::Settings::getIsFilteringEnabled()
             &&(current_index_rss_articles_+1)<rss_data_.getArticlesSize())
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

    if (Jelyazka::Settings::getIsFilteringEnabled()
        && current_index_rss_articles_<filtered_articles_.size())
    {
        return filtered_articles_[current_index_rss_articles_];
    }

    else if (!Jelyazka::Settings::getIsFilteringEnabled()
             && current_index_rss_articles_<rss_data_.getArticlesSize())
    {
        return rss_data_.articleAt(current_index_rss_articles_);
    }
    result.setLink("No data");
    result.setTitle("No data");
    result.setText("No data.");
    return result;
}

void  ArticleManager::setRssData (const RSSData &rss_data)
{
    //ToDo: optimize it
    rss_data_ = rss_data;
    current_index_rss_articles_ = 0;
    filtered_articles_.clear();
    data_base_.getFilterList(filters_);
    filterArticles();
}

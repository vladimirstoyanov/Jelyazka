#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <vector>

#include "database.h"
#include "rss_article.h"
#include "rss_data.h"
#include "search.h"
#include "settings.h"


class ArticleManager
{
public:
    ArticleManager(const RSSData &rss_data);
    virtual ~ArticleManager () = default;
    RSSArticle getNextRssArticle ();
    RSSArticle getPreviousRssArticle ();
    RSSArticle getCurrentRssArticle ();
    void setRssData (const RSSData &rss_data);

private:
    void filterArticles ();
    bool isArticleContainsFilters (const RSSArticle & article);

private:
    int current_index_rss_articles_;
    DataBase data_base_;
    std::vector<QString> filters_;
    std::vector<RSSArticle> filtered_articles_;
    RSSData rss_data_;

};

#endif // ARTICLEMANAGER_H

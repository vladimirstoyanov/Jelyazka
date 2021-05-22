#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <vector>

#include "database.h"
#include "rss_article.h"
#include "rss_data.h"
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
    int current_index_rss_articles_;
    DataBase data_base_;
    RSSData rss_data_;

};

#endif // ARTICLEMANAGER_H

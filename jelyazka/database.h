#ifndef DB_H
#define DB_H

//#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <vector>

#include <QtSql/QtSql>

#include "data.h"
#include "RSS/rssdata.h"
#include "RSS/rssarticle.h"

class DataBase
{
public:
    DataBase();
    virtual ~DataBase ();

    void    createTables();
    void    dropRssDataTable ();
    int     deleteAllFromAllURL();
    void    getFeeds(std::vector<QString> *l_old_view_feed);
    void    getCollectFeeds(std::vector<QString> *l_old_collect_feed);
    void    getCollectFeedsThatContainingText(const QString &text, std::vector<QString> *l_favorite_rss); //cf_find_feeds text changed event
    void    getFilterList(std::vector<QString> *l_old_filters);
    std::map<QString, RSSData> getRssData();
    QString getURLByName(const QString &name);
    void    getURLs(std::vector<QString> *urls);
    QString getVersionByName(const QString &name);
    int     insertIntoAllURLs(const QString &);
    void    insertIntoFavoriteFeeds(const QString &name, const QString &url, const QString &version);
    void    insertIntoCollectFeeds(const QString &name, const QString &url, const QString &version);
    void    insertIntoRssDataTable(const QString &name
                                , const QString &title
                                , const QString &link
                                , const QString &description);
    void    insertRowToFiltersTable(const QString &filter_name);
    void    loadStrctureFromDB(std::shared_ptr<Data> data);
    void    removeDataFromRSSTable(const QString &site_name, const bool all_data);
    void    removeDataFromFilters();
    void    removeDataFromCollectFeeds(const QString &site_name);
    int     selectURLFromAllURLs(const QString &);


private:
    void closeDB();
    void createAllURLTable();
    void createCollectFeedsTable();
    void createFavoriteFeedsTable();
    void createFiltersTable();
    void createRssDataTable();
    void createTable (const QString &table_name, const QString &query_string);
    int  dropTable(const QString &table_name);
    void openDB();

private:
    QSqlDatabase q_sql_data_base_;
};

#endif // DB_H

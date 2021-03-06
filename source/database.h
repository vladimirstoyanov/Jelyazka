#ifndef DB_H
#define DB_H

#include <map>
#include <vector>

#include <QtSql/QtSql>

#include "RSS/rss_data.h"
#include "RSS/rss_article.h"

class DataBase
{
public:
    DataBase();
    virtual ~DataBase ();

    void    createTables();
    void    dropRssDataTable ();
    int     deleteAllFromAllURL();
    void    getFeeds(std::vector<QString> *l_old_view_feed);
    void    getFilterList(std::vector<QString> &l_old_filters);
    std::map<QString, RSSData> getRssData();
    QString getURLByName(const QString &name);
    std::vector<QString> getURLs();
    std::vector<QString> getNewUrls();
    QString getVersionByName(const QString &name);
    int     insertIntoAllURLs(const QString &);
    void    insertIntoFeedList(const QString &name, const QString &url, const QString &version);
    void    insertIntoNewRssFeeds(const QString &name, const QString &url, const QString &version);
    void    insertIntoRssDataTable(const QString &name
                                , const QString &title
                                , const QString &link
                                , const QString &description);
    void    insertRowToFiltersTable(const QString &filter_name);
    void    removeAllDataFromRssData();
    void    removeAllDataFromNewRssFeeds();
    void    removeDataFromRssData(const QString &site_name);
    void    removeDataFromFilters();
    void    removeDataFromFeedList(const QString &site_name);
    int     selectURLFromAllURLs(const QString &);
    void    updateArticles(const RSSData &rss_data, std::vector<RSSData> & new_rss_data);

private:
    void closeDB();
    void createAllURLTable();
    void createFeedListTable();
    void createFiltersTable();
    void createNewRssFeeds();
    void createRssDataTable();
    void createTable (const QString &table_name, const QString &query_string);
    int  dropTable(const QString &table_name);
    void openDB();

private:
    QSqlDatabase q_sql_data_base_;
};

#endif // DB_H

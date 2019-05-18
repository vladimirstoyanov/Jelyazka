#ifndef DB_H
#define DB_H

//#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

#include <QtSql/QtSql>

#include "data.h"
#include "rssdata.h"

class DataBase
{
public:
    DataBase();
    //ToDo: create destructor that clears q_sql_data_base_
    void createTables();
    void getFeeds(std::vector<QString> *l_old_view_feed);
    void getCollectFeeds(std::vector<QString> *l_old_collect_feed);
    void getCollectFeedsThatContainingText(QString text, std::vector<QString> *l_favorite_rss); //cf_find_feeds text changed event
    void getFilterList(std::vector<QString> *l_old_filters);
    void insertIntoFavoriteFeeds(QString name, QString url, QString version);
    void insertIntoCollectFeeds(QString name, QString url, QString version);
    void insertRowToFiltersTable(QString filter_name);
    void loadStrctureFromDB(std::shared_ptr<Data> data);
    void removeDataFromRSSTable(QString site_name, bool all_data);
    void removeDataFromFilters();
    void removeDataFromCollectFeeds(QString site_name);

public:
    int deleteAllFromAllURL();
    int insertIntoAllURLs(QString);
    int selectURLFromAllURLs(QString);

public:
    QString getURLByName(const QString &name);
    QString getVersionByName(const QString &name);

private:
    void closeDB();
    void createAllURLTable();
    void createCollectFeedsTable();
    void createFavoriteFeedsTable();
    void createFiltersTable();
    void openDB();

private:
    QSqlDatabase q_sql_data_base_;
};

#endif // DB_H

#ifndef DB_H
#define DB_H

#include <QtSql/QtSql>
#include "rssdata.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "data.h"

class DataBase
{
public:
    DataBase();
    void createTables();
    void loadStrctureFromDB(Data *data);
    void getFavoriteFeeds(boost::ptr_vector<QString> *l_old_view_feed);
    void removeDataFromRSSTable(QString site_name, bool all_data);

    void insertIntoFavoriteFeeds(QString name, QString url, QString version);
    void insertIntoCollectFeeds(QString name, QString url, QString version);
    int insertIntoAllURLs(QString);

    QString getURLByName(const QString &name);
    QString getVersionByName(const QString &name);
    int selectURLFromAllURLs(QString);
    int deleteAllFromAllURL();

    void getCollectFeeds(boost::ptr_vector<QString> *l_old_collect_feed);
    void getFilterList(boost::ptr_vector<QString> *l_old_filters);
    void insertRowToFiltersTable(QString filter_name);
    void removeDataFromFilters();
    void removeDataFromCollectFeeds(QString site_name);
    void getCollectFeedsThatContainingText(QString text, boost::ptr_vector<QString> *l_favorite_rss); //cf_find_feeds text changed event

private:
    QSqlDatabase q_sql_data_base_;

    void openDB();
    void closeDB();
    void createCollectFeedsTable();
    void createAllURLTable();
    void createFavoriteFeedsTable();
    void createFiltersTable();
};

#endif // DB_H

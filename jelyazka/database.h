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

    void findAndReturnURLAndVersion(QString site_name, QString &url, QString &version);
    int selectURLFromAllURLs(QString);
    int deleteAllFromAllURL();



    void getCollectFeeds(boost::ptr_vector<QString> *l_old_collect_feed);
    void getFilterList(boost::ptr_vector<QString> *l_old_filters);
    void insertRowToFiltersTable(QString filter_name);
    void removeDataFromFilters();
    void removeDataFromCollectFeeds(QString site_name);
    void getCollectFeedsThatContainingText(QString text, boost::ptr_vector<QString> *l_favorite_rss); //cf_find_feeds text changed event

private:
    QSqlDatabase sqliteDataBase;

    void openDB();
    void closeDB();


};

#endif // DB_H

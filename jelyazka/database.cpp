#include "database.h"

DataBase::DataBase()
{
    //open db
    q_sql_data_base_ = QSqlDatabase::addDatabase("QSQLITE");
    q_sql_data_base_.setDatabaseName("sites.db3");
    q_sql_data_base_.open();

    //loadStrctureFromDB();
}

void DataBase::createTables()
{
    createCollectFeedsTable();
    createAllURLTable();
    createFavoriteFeedsTable();
    createFiltersTable();
}

void DataBase::loadStrctureFromDB(Data *data)
{
    //open data base
    //openDB();

    QSqlQuery query;

    createTables();

    //get all rss feeds urls
    query.prepare( "SELECT * FROM favorite_feeds" );

    if( !query.exec() )
    {
        qDebug()<<"Some error, when trying to read from \'favorite_feeds\' table...";
        return;
    }

    while( query.next() )
    {
        RSSData *rssData = new RSSData();
        rssData->setSiteName(query.value( 1 ).toByteArray().data());
        rssData->setURL(query.value( 2 ).toByteArray().data());
        rssData->setType("RSS");
        rssData->setVersion(query.value(3).toByteArray().data());
        data->pushBack(rssData);
    }
    //close data base
    //closeDB();
}

void DataBase::openDB()
{
    //open db
    q_sql_data_base_ = QSqlDatabase::addDatabase("QSQLITE");
    q_sql_data_base_.setDatabaseName("sites.db3");
    q_sql_data_base_.open();
}

void DataBase::closeDB()
{
   q_sql_data_base_.close();
}

//fill view_feeds (QListWidget var)
void DataBase::getFavoriteFeeds(boost::ptr_vector<QString> *l_old_view_feed)
{
    QSqlQuery query;

    query.prepare( "SELECT * FROM favorite_feeds" );

    if( !query.exec() )
    {
        qDebug()<<"Some error, when trying to read from \'favorite_feeds' table...";
        return;
    }

    l_old_view_feed->clear();

    while(query.next())
    {
        QString *name = new QString;
        *name = query.value(1).toByteArray().data();
        l_old_view_feed->push_back(name);
    }
}

//remove site_name data from 'rss' table in 'sites.db3'. If all_data == 1,
//then remove all data from 'rss' table
void DataBase::removeDataFromRSSTable(QString site_name, bool all_data)
{

    QSqlQuery query;

    if (all_data)
    {
        query.prepare("delete from favorite_feeds");
        if (!query.exec())
            qDebug()<<"Fail:" + query.lastError().text();
        return;
    }

    query.prepare(QString("delete from favorite_feeds where name=\'%1\'").arg(site_name));
    if (!query.exec())
        qDebug()<<"Fail:" + query.lastError().text();
}

//insert row to 'rss' DB table
void DataBase::insertIntoFavoriteFeeds(QString name, QString url, QString version)
{
    QSqlQuery query;

    query.prepare("insert into favorite_feeds (name, url, version) values (\'"+ name+"\',\'" + url+ "\',\'" + version + "\')");
    if (!query.exec())
    {
        qDebug()<<"Fail:" + query.lastError().text();
    }
}

void DataBase::insertIntoCollectFeeds(QString name, QString url, QString version)
{
    QSqlQuery query;

    query.prepare("insert into collect_feeds (name, url, version) values (\'"+ name+"\',\'" + url+ "\',\'" + version + "\')");
    if (!query.exec())
    {
        qDebug()<<"Fail:" + query.lastError().text();
    }
}

int DataBase::insertIntoAllURLs(QString url)
{
    QSqlQuery query;

    if (!query.exec("insert into all_urls (url) values (\'" + url+ "\')"))
    {
        qDebug()<<"Error insert: "  + url;
        return 0;
    }

    return 1;
}

QString DataBase::getURLByName(const QString &name)
{
    QSqlQuery query;

    if (q_sql_data_base_.isOpen())
    {
        query.prepare(QString("SELECT * FROM collect_feeds WHERE name=\"%1\"").arg(name));
        if (!query.exec())
        {
            qDebug()<<"Fail:" + query.lastError().text();
            return "";
        }
        if(query.next())
        {
            return query.value( 2 ).toByteArray().data();
        }
    }
    qDebug()<<"[DataBase::getURLByName] DB is not opened...";
    return "";
}

QString DataBase::getVersionByName(const QString &name)
{
    QSqlQuery query;

    if (q_sql_data_base_.isOpen())
    {
        query.prepare(QString("SELECT * FROM collect_feeds WHERE name=\"%1\"").arg(name));
        if (!query.exec())
        {
            qDebug()<<"Fail:" + query.lastError().text();
            return "";
        }
        if(query.next())
        {
            return query.value( 2 ).toByteArray().data();
        }
    }
    qDebug()<<"[DataBase::getVersionByName] DB is not opened...";
    return "";
}

int DataBase::selectURLFromAllURLs(QString url)
{
        QSqlQuery query;

        if( !query.exec("SELECT url FROM all_urls WHERE url=\'" + url + "\'") )
        {
            qDebug()<<"Error select: "  + url;
            return 0 ;
        }

        while( query.next() )
            return 1;

        return 0;
}

int DataBase::deleteAllFromAllURL()
{
    QSqlQuery query;
    query.prepare("delete from all_urls");
    if (!query.exec())
        qDebug()<<"Fail delete:" + query.lastError().text();

    return 1;
}


void DataBase::getCollectFeeds(boost::ptr_vector<QString> *l_old_collect_feed)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM collect_feeds");

    if(!query.exec())
    {
        qDebug()<<"OptionsWindow::fillCollectListView(): Some error, when trying to read from \'site_name' table...";
        return;
    }
    l_old_collect_feed->clear();

    while( query.next() )
    {
        QString *name = new QString;
        *name = query.value( 1 ).toByteArray().data();
        l_old_collect_feed->push_back(name);
    }
}

void DataBase::getFilterList(boost::ptr_vector<QString> *l_old_filters)
{
    QSqlQuery query;

    query.prepare( "SELECT * FROM filters" );

    if( !query.exec() )
    {
        qDebug()<<"void OptionsWindow::fillFilterListView(): Some error, when trying to read from \'filters' table...";
        return;
    }

    l_old_filters->clear(); //clear old list

    //fill with new data
    while( query.next() )
    {
        QString *filter = new QString;
        *filter = query.value( 1 ).toByteArray().data();
        //if (!addStringToFilterList(*filter))
        l_old_filters->push_back(filter);
    }
}


void DataBase::insertRowToFiltersTable(QString filter_name)
{
    QSqlQuery query;

    query.prepare("insert into filters (filter) values (\'"+ filter_name+"\')");
    if (!query.exec())
    {
        qDebug()<<"DB::insertRowToFiltersTable(QString filter_name) fail:" + query.lastError().text();
    }
}

void DataBase::removeDataFromFilters()
{
    QSqlQuery query;

    query.prepare("delete from filters");

    if (!query.exec())
        qDebug()<<"DB::removeDataFromFilters(QString filter_name, bool all_data) fail:" + query.lastError().text();
}

void DataBase::removeDataFromCollectFeeds(QString site_name)
{
    QSqlQuery query;

    query.prepare(QString("delete from collect_feeds where name=\"%1\"").arg(site_name));
    if (!query.exec())
        qDebug()<<"DB::removeDataFromCollectFeeds(QString site_name) fail delete from collect_feeds where filter... " + query.lastError().text();
}

void DataBase::getCollectFeedsThatContainingText(QString text, boost::ptr_vector<QString> *l_favorite_rss) //cf_find_feeds text changed event
{
    QSqlQuery query;

    query.prepare( "SELECT * FROM collect_feeds" );

    if( !query.exec() )
    {
        qDebug()<<"Some error, when trying to read from \'site_name' table...";
        return;
    }

    while( query.next() )
    {
        QString *name = new QString(query.value( 1 ).toByteArray().data());
        if (name->contains(text))
            l_favorite_rss->push_back(name);
    }
}


void DataBase::createCollectFeedsTable()
{
    if (!q_sql_data_base_.tables().contains(QLatin1String("collect_feeds"))) //if there isn't 'collect_feeds' table
    {
        //create 'collect_feeds'table
        if (q_sql_data_base_.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table collect_feeds "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "name varchar, "
                          "url varchar, "
                          "version integer)"))
                {
                    qDebug()<<"Can't create table: collect_feeds";
                }
        }
    }
}

void DataBase::createAllURLTable()
{

    //"all_urls" table
    if (!q_sql_data_base_.tables().contains(QLatin1String("all_urls"))) //if there isn't 'all_urls' table
    {
        //create 'collect_feeds' table
        if (q_sql_data_base_.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table all_urls "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "url varchar)"))
                {
                    qDebug()<<"Can't create table: all_urls";
                }
        }
    }
}

void DataBase::createFavoriteFeedsTable()
{
    if (!q_sql_data_base_.tables().contains(QLatin1String("favorite_feeds"))) //if there isn't 'rss' table
    {
        //create 'rss'table
        if (q_sql_data_base_.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table favorite_feeds "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "name varchar, "
                          "url varchar, "
                          "version integer)"))
                {
                     qDebug()<<"Can't create table: rss";
                }
        }
    }
}

void DataBase::createFiltersTable()
{
    if (!q_sql_data_base_.tables().contains(QLatin1String("filters"))) //if there isn't 'rss' table
    {
        //create 'rss' table
        if (q_sql_data_base_.isOpen())
        {
                QSqlQuery query;
                if (!query.exec("create table filters "
                          "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                          "filter varchar)"))
                {
                     qDebug()<<"Can't create table: filters";
                }
        }
    }
}

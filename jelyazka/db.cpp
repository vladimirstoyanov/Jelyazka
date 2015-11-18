#include "db.h"

DB::DB()
{
    //open db
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("sites.db3");
    sqliteDataBase.open();

    //loadStrctureFromDB();
}


/////////sitestruct.h
///
void DB::createTables()
{
    //open data base
    //openDB();

    //"collec_feeds" table
    if (!sqliteDataBase.tables().contains(QLatin1String("collect_feeds"))) //if hasn't 'collect_feeds' table
    {
        //create 'collect_feeds'table
        if (sqliteDataBase.isOpen())
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

    //"all_urls" table
    if (!sqliteDataBase.tables().contains(QLatin1String("all_urls"))) //if hasn't 'all_urls' table
    {
        //create 'collect_feeds' table
        if (sqliteDataBase.isOpen())
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

    //"rss" table
    if (!sqliteDataBase.tables().contains(QLatin1String("favorite_feeds"))) //if hasn't 'rss' table
    {
        //create 'rss'table
        if (sqliteDataBase.isOpen())
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

    //"filter" table
    if (!sqliteDataBase.tables().contains(QLatin1String("filters"))) //if hasn't 'rss' table
    {
        //create 'rss' table
        if (sqliteDataBase.isOpen())
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

    //close data base
    //closeDB();
}

void DB::loadStrctureFromDB(Data *data)
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
        data->push_back(rssData);
    }
    //close data base
    //closeDB();
}

void DB::openDB()
{
    //open db
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("sites.db3");
    sqliteDataBase.open();
}

void DB::closeDB()
{
   sqliteDataBase.close();
}




////////options.cpp
///
//fill view_feeds (QListWidget var)
void DB::getFavoriteFeeds(boost::ptr_vector<QString> *l_old_view_feed)
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
void DB::removeDataFromRSSTable(QString site_name, bool all_data)
{

    QSqlQuery qry;

    if (all_data)
    {
        qry.prepare("delete from favorite_feeds");
        if (!qry.exec())
            qDebug()<<"Fail:" + qry.lastError().text();
        return;
    }

    qry.prepare(QString("delete from favorite_feeds where name=\'%1\'").arg(site_name));
    if (!qry.exec())
        qDebug()<<"Fail:" + qry.lastError().text();
}

//insert row to 'rss' DB table
void DB::insertIntoFavoriteFeeds(QString name, QString url, QString version)
{
    QSqlQuery qry;

    qry.prepare("insert into favorite_feeds (name, url, version) values (\'"+ name+"\',\'" + url+ "\',\'" + version + "\')");
    if (!qry.exec())
    {
        qDebug()<<"Fail:" + qry.lastError().text();
    }
}

void DB::insertIntoCollectFeeds(QString name, QString url, QString version)
{
    QSqlQuery qry;

    qry.prepare("insert into collect_feeds (name, url, version) values (\'"+ name+"\',\'" + url+ "\',\'" + version + "\')");
    if (!qry.exec())
    {
        qDebug()<<"Fail:" + qry.lastError().text();
    }
}

int DB::insertIntoAllURLs(QString url)
{
    QSqlQuery query;

    if (!query.exec("insert into all_urls (url) values (\'" + url+ "\')"))
    {
        qDebug()<<"Error insert: "  + url;
        return 0;
    }

    return 1;
}

//from site_name, return url and version
void DB::findAndReturnURLAndVersion(QString site_name, QString &url, QString &version)
{
    QSqlQuery query;
    url = "";
    version="";

    if (sqliteDataBase.isOpen())
    {
        query.prepare(QString("SELECT * FROM collect_feeds WHERE name=\"%1\"").arg(site_name));
        if (!query.exec())
        {
            qDebug()<<"Fail:" + query.lastError().text();
            url = "";
            version = "";
            return;
        }
        if(query.next())
        {
            url = query.value( 2 ).toByteArray().data();
            version = query.value(3).toByteArray().data();
        }
    }
}

int DB::selectURLFromAllURLs(QString url)
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

int DB::deleteAllFromAllURL()
{
    QSqlQuery query;
    query.prepare("delete from all_urls");
    if (!query.exec())
        qDebug()<<"Fail delete:" + query.lastError().text();

    return 1;
}


void DB::getCollectFeeds(boost::ptr_vector<QString> *l_old_collect_feed)
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

void DB::getFilterList(boost::ptr_vector<QString> *l_old_filters)
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


void DB::insertRowToFiltersTable(QString filter_name)
{
    QSqlQuery qry;

    qry.prepare("insert into filters (filter) values (\'"+ filter_name+"\')");
    if (!qry.exec())
    {
        qDebug()<<"DB::insertRowToFiltersTable(QString filter_name) fail:" + qry.lastError().text();
    }
}

void DB::removeDataFromFilters(QString filter_name, bool all_data)
{
    QSqlQuery qry;

    if (all_data)
        qry.prepare("delete from filters");
    else
        qry.prepare(QString("delete from filters where name=\"%1\"").arg(filter_name));
    if (!qry.exec())
        qDebug()<<"DB::removeDataFromFilters(QString filter_name, bool all_data) fail:" + qry.lastError().text();
}

void DB::removeDataFromCollectFeeds(QString site_name)
{
    QSqlQuery qry;

    qry.prepare(QString("delete from collect_feeds where name=\"%1\"").arg(site_name));
    if (!qry.exec())
        qDebug()<<"DB::removeDataFromCollectFeeds(QString site_name) fail delete from collect_feeds where filter... " + qry.lastError().text();
}

void DB::getCollectFeedsThatContainingText(QString text, boost::ptr_vector<QString> *l_favorite_rss) //cf_find_feeds text changed event
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

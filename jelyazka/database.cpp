#include "database.h"

DataBase::DataBase()
{
    //open db
    openDB();
    createTables(); //it creates RSS data necessary tables if they don't exist
}

DataBase::~DataBase ()
{
    closeDB();
}

void DataBase::createTables()
{
    createCollectFeedsTable();
    createAllURLTable();
    createFavoriteFeedsTable();
    createFiltersTable();
    createRssDataTable();
}

void DataBase::loadStrctureFromDB(std::shared_ptr<Data> data)
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
        std::shared_ptr<RSSData> rssData = std::make_shared<RSSData>();
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
    q_sql_data_base_.setDatabaseName("../resources/sites.db3");
    q_sql_data_base_.open();
}

void DataBase::closeDB()
{
    //q_sql_data_base_.close();
    QSqlDatabase db = QSqlDatabase::database();
    db.close();

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}

//fill view_feeds (QListWidget var)
void DataBase::getFeeds(std::vector<QString> *l_old_view_feed)
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
        QString name;
        name = query.value(1).toByteArray().data();
        l_old_view_feed->push_back(name);
    }
}

void DataBase::removeDataFromRSSTable(const QString &site_name, const bool all_data)
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

void DataBase::insertIntoFavoriteFeeds(const QString &name, const QString &url, const QString &version)
{
    QSqlQuery query;
    query.prepare("insert into favorite_feeds (name, url, version) values (?,?,?)");
    query.addBindValue(name);
    query.addBindValue(url);
    query.addBindValue(version);

    if (!query.exec())
    {
        qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
    }
}

void DataBase::insertIntoCollectFeeds(const QString &name, const QString &url, const QString &version)
{
    QSqlQuery query;
    query.prepare("insert into collect_feeds (name, url, version) values (?,?,?)");
    query.addBindValue(name);
    query.addBindValue(url);
    query.addBindValue(version);

    if (!query.exec())
    {
        qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
    }
}

int DataBase::insertIntoAllURLs(const QString &url)
{
    QSqlQuery query;
    query.prepare("insert into all_urls (url) values (?)");
    query.addBindValue(url);

    if (!query.exec())
    {
        qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
        return 0;
    }

    return 1;
}

void DataBase::insertIntoRssDataTable(const QString &name
                                     , const QString &title
                                     , const QString &link
                                     , const QString &description)
{

    QSqlQuery query;
    query.prepare("insert into rss_data (name, title, url, description) values (?,?,?,?)");
    query.addBindValue(name);
    query.addBindValue(title);
    query.addBindValue(link);
    query.addBindValue(description);

    if (!query.exec())
    {
        qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
    }
}

void DataBase::dropRssDataTable()
{
    dropTable ("rss_data");
}

int DataBase::dropTable(const QString &table_name)
{
    QSqlQuery query;

    if (!query.exec("drop table " + table_name))
    {
        qDebug()<<__PRETTY_FUNCTION__<<"Error drop table: "  + table_name;
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

int DataBase::selectURLFromAllURLs(const QString &url)
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


void DataBase::getCollectFeeds(std::vector<QString> *l_old_collect_feed)
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
        QString name;
        name = query.value( 1 ).toByteArray().data();
        l_old_collect_feed->push_back(name);
    }
}

void DataBase::getFilterList(std::vector<QString> *l_old_filters)
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
        QString filter;
        filter = query.value( 1 ).toByteArray().data();
        //if (!addStringToFilterList(*filter))
        l_old_filters->push_back(filter);
    }
}


void DataBase::insertRowToFiltersTable(const QString &filter_name)
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

void DataBase::removeDataFromCollectFeeds(const QString &site_name)
{
    QSqlQuery query;

    query.prepare(QString("delete from collect_feeds where name=\"%1\"").arg(site_name));
    if (!query.exec())
        qDebug()<<"DB::removeDataFromCollectFeeds(QString site_name) fail delete from collect_feeds where filter... " + query.lastError().text();
}

void DataBase::getCollectFeedsThatContainingText(const QString &text, std::vector<QString> *l_favorite_rss) //cf_find_feeds text changed event
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
        QString name = query.value( 1 ).toByteArray().data();
        if (name.contains(text))
            l_favorite_rss->push_back(name);
    }
}


void DataBase::createCollectFeedsTable()
{
    createTable ("collect_feeds",
                 "create table collect_feeds "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "name varchar, "
                 "url varchar, "
                 "version integer)");
}

void DataBase::createAllURLTable()
{
    createTable ("all_urls",
                 "create table all_urls "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "url varchar)");
}

void DataBase::createFavoriteFeedsTable()
{
    createTable ("favorite_feeds",
                 "create table favorite_feeds "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "name varchar, "
                 "url varchar, "
                 "version integer)");
}

void DataBase::createFiltersTable()
{
    createTable ("filters",
                 "create table filters "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "filter varchar)");
}

void DataBase::createRssDataTable()
{
    createTable("rss_data",
                "create table rss_data "
                "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                "name varchar, "
                "title varchar, "
                "url varchar, "
                "description varchar)");
}

void DataBase::createTable (const QString &table_name, const QString &query_string)
{
    if (!q_sql_data_base_.tables().contains(table_name)) //if the table doesn't exist
    {
        //create 'table'
        if (q_sql_data_base_.isOpen())
        {
                QSqlQuery query;
                if (!query.exec(query_string))
                {
                    qDebug()<<"Can't create table: rss_data";
                }
        }
    }
}

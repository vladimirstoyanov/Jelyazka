#include "database.h"

DataBase::DataBase()
{
    //open db
    //openDB();
    //createTables(); //it creates RSS data necessary tables if they don't exist
}

DataBase::~DataBase ()
{
    //closeDB();
}

void DataBase::createTables()
{
    createAllURLTable();
    createFeedListTable();
    createFiltersTable();
    createRssDataTable();
    createNewRssFeeds();
}

void DataBase::openDB()
{
    //qDebug()<<__PRETTY_FUNCTION__;
    //open db
    q_sql_data_base_ = QSqlDatabase::addDatabase("QSQLITE");
    q_sql_data_base_.setDatabaseName("../resources/jelyazka_db.db3");
    q_sql_data_base_.open();
}

void DataBase::closeDB()
{
    //qDebug()<<__PRETTY_FUNCTION__;
    //q_sql_data_base_.close();
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    q_sql_data_base_.close();

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    //QSqlDatabase::removeDatabase("QSQLITE");
    //  'qt_sql_default_connection'
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    //qDebug()<<__PRETTY_FUNCTION__<<": END";
}

std::map<QString, RSSData> DataBase::getRssData ()
{
    std::map<QString, RSSData> result;
    std::map<QString, RSSData>::iterator it;
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare( "SELECT * FROM rss_data" );

        if( !query.exec() )
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
            closeDB();
            return result;
        }

        while(query.next())
        {
            RSSData rss_data;
            RSSArticle rss_article;
            rss_article.setTitle(query.value(2).toByteArray().data());
            rss_article.setLink( query.value(3).toByteArray().data());
            rss_article.setText( query.value(4).toByteArray().data());
            QString  name = query.value(1).toByteArray().data();

            it = result.find(name);
            if (it==result.end())
            {
                rss_data.setSiteName(name);
                rss_data.articlesPushBack(rss_article);
                result[name] = rss_data;
            }
            else
            {
                it->second.articlesPushBack(rss_article);
            }
        }
    }
    closeDB();
}

//fill view_feeds (QListWidget var)
std::vector<QString> DataBase::getURLs()
{
    std::vector<QString> urls;
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare( "SELECT * FROM feed_list" );

        if( !query.exec() )
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
            closeDB();
            return urls;
        }

        while(query.next())
        {
            QString name;
            name = query.value(2).toByteArray().data();
            urls.push_back(name);
        }
    }
    closeDB();
    return urls;
}

std::vector<QString> DataBase::getNewUrls()
{
    std::vector<QString> urls;
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare( "SELECT * FROM new_rss_feeds" );

        if( !query.exec() )
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
            closeDB();
            return urls;
        }

        while(query.next())
        {
            QString name;
            name = query.value(2).toByteArray().data();
            urls.push_back(name);
        }
    }
    closeDB();
    return urls;
}

//fill view_feeds (QListWidget var)
void DataBase::getFeeds(std::vector<QString> *l_old_view_feed)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare( "SELECT * FROM feed_list" );

        if( !query.exec() )
        {
            qDebug()<<"Some error, when trying to read from \'feed_list' table...";
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
    closeDB();
}

void DataBase::removeAllDataFromRssData()
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);


            query.prepare("delete from rss_data");
            if (!query.exec())
            {
                qDebug()<<"Fail:" + query.lastError().text();
            }
    }
    closeDB();
}


void DataBase::removeAllDataFromNewRssFeeds()
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);


            query.prepare("delete from new_rss_feeds");
            if (!query.exec())
            {
                qDebug()<<"Fail:" + query.lastError().text();
            }
    }
    closeDB();
}

void DataBase::removeDataFromRssData(const QString &site_name)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare(QString("delete from rss_data where name=\'%1\'").arg(site_name));
        if (!query.exec())
        {
            qDebug()<<"Fail:" + query.lastError().text();
        }
    }
    closeDB();
}

void DataBase::insertIntoFeedList(const QString &name, const QString &url, const QString &version)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);
        query.prepare("insert into feed_list (name, url, version) values (?,?,?)");
        query.addBindValue(name);
        query.addBindValue(url);
        query.addBindValue(version);

        if (!query.exec())
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
        }
    }
    closeDB();
}

void DataBase::insertIntoNewRssFeeds(const QString &name, const QString &url, const QString &version)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);
        query.prepare("insert into new_rss_feeds (name, url, version) values (?,?,?)");
        query.addBindValue(name);
        query.addBindValue(url);
        query.addBindValue(version);

        if (!query.exec())
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
        }
    }
    closeDB();
}

int DataBase::insertIntoAllURLs(const QString &url)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);
        query.prepare("insert into all_urls (url) values (?)");
        query.addBindValue(url);

        if (!query.exec())
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
            closeDB();
            return 0;
        }
    }
    closeDB();
    return 1;
}

void DataBase::insertIntoRssDataTable(const QString &name
                                     , const QString &title
                                     , const QString &url
                                     , const QString &description)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);
        query.prepare("insert into rss_data (name, title, url, description) values (:name,:title,:url,:desc)");
        query.bindValue(":name", name);
        query.bindValue(":title", title);
        query.bindValue(":url", url);
        query.bindValue(":desc",  description);

        if (!query.exec())
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error:"<<query.lastError();
        }
    }
    closeDB();
}

void DataBase::dropRssDataTable()
{
    dropTable ("rss_data");
}

int DataBase::dropTable(const QString &table_name)
{
    int result = 0;
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        if (!query.exec("drop table " + table_name))
        {
            qDebug()<<__PRETTY_FUNCTION__<<"Error drop table: "  + table_name;
        }
        result = 1;
    }
    closeDB();

    return result;
}

QString DataBase::getURLByName(const QString &name)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        if (q_sql_data_base_.isOpen())
        {
            query.prepare(QString("SELECT * FROM feed_list WHERE name=\"%1\"").arg(name));
            if (!query.exec())
            {
                qDebug()<<"Fail:" + query.lastError().text();
                closeDB();
                return "";
            }
            if(query.next())
            {
                closeDB();
                return query.value( 2 ).toByteArray().data();
            }
        }
        qDebug()<<"[DataBase::getURLByName] DB is not opened...";
    }
    closeDB();
    return "";
}

QString DataBase::getVersionByName(const QString &name)
{
    {
        openDB();
        QSqlQuery query (q_sql_data_base_);

        if (q_sql_data_base_.isOpen())
        {
            query.prepare(QString("SELECT * FROM feed_list WHERE name=\"%1\"").arg(name));
            if (!query.exec())
            {
                qDebug()<<"Fail:" + query.lastError().text();
                closeDB();
                return "";
            }
            if(query.next())
            {
                closeDB();
                return query.value( 2 ).toByteArray().data();
            }
        }
        qDebug()<<"[DataBase::getVersionByName] DB is not opened...";
    }
    closeDB();
    return "";
}

int DataBase::selectURLFromAllURLs(const QString &url)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        if( !query.exec("SELECT url FROM all_urls WHERE url=\'" + url + "\'") )
        {
            qDebug()<<"Error select: "  + url;
            closeDB();
            return 0 ;
        }

        while( query.next() )
        {
            closeDB();
            return 1;
        }
    }
    closeDB();
    return 0;
}

int DataBase::deleteAllFromAllURL()
{
    {
        openDB();
        QSqlQuery query (q_sql_data_base_);
        query.prepare("delete from all_urls");
        if (!query.exec())
        {
            qDebug()<<"Fail delete:" + query.lastError().text();
        }
    }
    closeDB();
    return 1;
}

void DataBase::getFilterList(std::vector<QString> &l_old_filters)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare( "SELECT * FROM filters" );

        if( !query.exec() )
        {
            qDebug()<<"void OptionsWindow::fillFilterListView(): Some error, when trying to read from \'filters' table...";
            closeDB();
            return;
        }

        l_old_filters.clear(); //clear old list

        //fill with new data
        while( query.next() )
        {
            QString filter;
            filter = query.value( 1 ).toByteArray().data();
            //if (!addStringToFilterList(*filter))
            l_old_filters.push_back(filter);
        }
    }
    closeDB();
}


void DataBase::insertRowToFiltersTable(const QString &filter_name)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare("insert into filters (filter) values (\'"+ filter_name+"\')");
        if (!query.exec())
        {
            qDebug()<<"DB::insertRowToFiltersTable(QString filter_name) fail:" + query.lastError().text();
        }
    }
    closeDB();
}

void DataBase::removeDataFromFilters()
{
    {
        openDB();
        QSqlQuery query (q_sql_data_base_);

        query.prepare("delete from filters");

        if (!query.exec())
        {
            qDebug()<<"DB::removeDataFromFilters(QString filter_name, bool all_data) fail:" + query.lastError().text();
        }
    }
    closeDB();
}

void DataBase::removeDataFromFeedList(const QString &site_name)
{
    {
        openDB();
        QSqlQuery query(q_sql_data_base_);

        query.prepare(QString("delete from feed_list where name=\"%1\"").arg(site_name));
        if (!query.exec())
        {
            qDebug()<<"DB::removeDataFromFavoriteFeeds(QString site_name) fail delete from feed_list where filter... " + query.lastError().text();
        }
    }
    closeDB();
}


void DataBase::createAllURLTable()
{
    createTable ("all_urls",
                 "create table all_urls "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "url varchar)");
}

void DataBase::createNewRssFeeds()
{
    createTable ("new_rss_feeds",
                 "create table new_rss_feeds "
                 "(id integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, "
                 "name varchar, "
                 "url varchar, "
                 "version integer)");
}

void DataBase::createFeedListTable()
{
    createTable ("feed_list",
                 "create table feed_list "
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
    qDebug()<<__PRETTY_FUNCTION__<<": query:"<<query_string;
    {
        openDB();
        if (!q_sql_data_base_.tables().contains(table_name)) //if the table doesn't exist
        {
            //create 'table'
            if (q_sql_data_base_.isOpen())
            {
                    QSqlQuery query;
                    if (!query.exec(query_string))
                    {
                        qDebug()<<__PRETTY_FUNCTION__<<":"<<query.lastError()<<" : query_string: "<<query_string;
                    }
            }
        }
    }
    closeDB();
}

void DataBase::updateArticles(const RSSData &rss_data, std::vector<RSSData> & new_rss_data)
{
    std::map<QString, RSSData>::iterator it;
    std::map<QString, RSSData> all_rss_data =  getRssData ();

    it = all_rss_data.find(rss_data.getSiteName());
    if (it == all_rss_data.end())
    {
        qDebug()<<__PRETTY_FUNCTION__<<": Web site name: "<<rss_data.getSiteName()<<" hasn't been found!";
        return;
    }

    for (size_t i=0; i<rss_data.getArticlesSize(); ++i)
    {
        for (size_t j=0; j<it->second.getArticlesSize(); ++j)
        {
            if (it->second.articleAt(j).getLink() == rss_data.articleAt(i).getLink())
            {
                break;
            }

            if (j==it->second.getArticlesSize()-1) //found a new article
            {
                insertIntoRssDataTable(rss_data.getSiteName()
                                                 , rss_data.articleAt(i).getTitle()
                                                 , rss_data.articleAt(i).getLink()
                                                 , rss_data.articleAt(i).getText());
                new_rss_data.push_back (rss_data);

            }
        }
    }
}

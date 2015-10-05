#include "db.h"

DB::DB()
{
    //open db
    sqliteDataBase = QSqlDatabase::addDatabase("QSQLITE");
    sqliteDataBase.setDatabaseName("sites.db3");
    sqliteDataBase.open();

    //loadStrctureFromDB();
}

void DB::createTables()
{
    //open data base
    openDB();

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
    closeDB();
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



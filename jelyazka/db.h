#ifndef DB_H
#define DB_H

#include <QtSql/QtSql>

class DB
{
public:
    DB();
    //void loadStrctureFromDB();
    void createTables();
private:
    QSqlDatabase sqliteDataBase;

    void openDB();
    void closeDB();

//signals:

//public slots:
};

#endif // DB_H

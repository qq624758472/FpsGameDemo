#ifndef _MYDB_H_
#define _MYDB_H_
#include <iostream>
#include <string>
#include <mysql/mysql.h>
using namespace std;

// sudo apt-get install libmysqlclient-dev
class MyDB
{
private:
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

public:
    MyDB();
    ~MyDB();
    bool initDb(string host, string user, string password, string db_name);
    bool execSql(string sql);
};
#endif

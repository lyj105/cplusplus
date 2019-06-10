#ifndef _DBMANAGER_H
#define _DBMANAGER_H
#include <string>
using namespace std;
#include "common.h"
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
//数据库配置信息
struct DBInfo
{
	string host="127.0.0.1";
	string user="root";
	string passwd="123456";
	string db="test";
	uint16_t port=3306;
};
class DBManager
{
public:
	DBManager();
	~DBManager();

	bool SelectDB(string dbName);
	bool ConnectDB(DBInfo &dbInfo);
	MYSQL_RES* ExeSql(const char * sql, unsigned long len);
	bool readFromSql(string fileName, vector<string>& sql);
	bool sourceSql(string fileName);
private:
	MYSQL *mysqlInit(DBInfo &info);
	void mysqlClose();
private:
	MYSQL *m_mysqlConn;
	DBInfo m_dbConfig;
};


extern DBManager g_DBManager;








#endif
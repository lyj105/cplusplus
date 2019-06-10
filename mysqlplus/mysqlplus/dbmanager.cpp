#include "pch.h"
#include "dbmanager.h"
#include <fstream>
DBManager g_DBManager;
DBManager::DBManager()
{
}
DBManager::~DBManager()
{
}
bool DBManager::ConnectDB(DBInfo &dbInfo)
{
	m_dbConfig = dbInfo;
	m_mysqlConn = mysqlInit(dbInfo);
	if (!m_mysqlConn)
	{
		return false;
	}
	return true;
}

MYSQL *DBManager::mysqlInit(DBInfo &info)
{
	MYSQL *mysql = mysql_init(NULL);
	if (!mysql)
		return NULL;

	if (!mysql_real_connect(mysql,
		info.host.c_str(),
		info.user.c_str(),
		info.passwd.c_str(),
		info.db.c_str(),
		info.port, NULL, 0))
	{
		int ret = mysql_errno(mysql);

		mysql_close(mysql);
		return NULL;
	}

#if MYSQL_VERSION_ID >= 50013
	my_bool reconnect = 1;
	if (mysql_options(mysql, MYSQL_OPT_RECONNECT, &reconnect))
	{
		int ret = mysql_errno(mysql);

		mysql_close(mysql);
		return NULL;
	}
#else
	mysql->reconnect = 1;
#endif


	return mysql;
}

void DBManager::mysqlClose()
{
	if (m_mysqlConn)
	{
		mysql_close(m_mysqlConn);
		m_mysqlConn = NULL;
	}
}
/************************************************************************/
/* ִ��SQL���                                                          */
/************************************************************************/
MYSQL_RES* DBManager::ExeSql(const char * sql, unsigned long len)
{
	MYSQL_RES* res = NULL;
	int ret = mysql_real_query(m_mysqlConn, sql, len);
	if (ret == 0)
	{
		res = mysql_store_result(m_mysqlConn);
	}
	else {
		printf("mysql query %s return errorcode:%d\n", sql, mysql_errno(m_mysqlConn));
	}
	return res;
}
/************************************************************************/
/* ѡ�����ݿ�                                                           */
/************************************************************************/
bool DBManager::SelectDB(string dbName)
{
	if (mysql_select_db(m_mysqlConn, dbName.c_str()))
		return false;
	else
		return true;
}
/************************************************************************/
/*fileName��sql�ļ���·����  ������fileName�е�ÿһ��sql��䣬���뵽sql������    */
/************************************************************************/
bool DBManager::readFromSql(string fileName, vector<string>& sql) {
	ifstream in(fileName.c_str(), ios::in);//linux
	string signalSql, s;
	if (!in) {
		return false;
	}
	while (getline(in, s)) {
		int pos = s.find(";");
		signalSql += s;
		if (pos != s.npos) {//�ҵ���һ�����Ľ���λ
			sql.push_back(signalSql);
			signalSql.clear();
		}
		s.clear();
	}
	in.close();
	return true;
}
/************************************************************************/
/* �������ݿ�sql                                                        */
/************************************************************************/
bool DBManager::sourceSql(string fileName) {
	vector<string> vecSql;
	bool ret = readFromSql(fileName, vecSql);
	if (ret == false) {
		printf("����gamedb.sqlʧ��");
		return false;
	}
	for (vector<string>::iterator it = vecSql.begin(); it != vecSql.end(); it++)
	{

		ExeSql((*it).c_str(), (*it).length());
	}
	return true;
}
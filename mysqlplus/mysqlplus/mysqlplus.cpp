// mysqlplus.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "dbmanager.h"
int main()
{
	DBManager* manaher = new DBManager;

	std::string  msql = "C:/Users/liyj/Desktop/test.sql";
	manaher->sourceSql(msql);

    std::cout << "Hello World!\n"; 
}


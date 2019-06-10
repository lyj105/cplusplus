// cplusplus.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "CParseIniFile.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;


static string  getCurrentTimeStr()
{
	time_t t = time(NULL);
	char ch[64] = { 0 };
	//strftime(ch, sizeof(ch) - 1, "%Y-%m-%d %H:%M:%S", localtime(&t));     //年-月-日 时-分-秒
	return ch;
}



static std::string  getTime() {
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

	   //格式化输出本地时间
	printf("年：%d\n", t.tm_year + 1900);
	printf("月：%d\n", t.tm_mon + 1);
	printf("日：%d\n", t.tm_mday);
	printf("周：%d\n", t.tm_wday);
	printf("一年中：%d\n", t.tm_yday);
	printf("时：%d\n", t.tm_hour);
	printf("分：%d\n", t.tm_min);
	printf("秒：%d\n", t.tm_sec);
	printf("夏令时：%d\n", t.tm_isdst);
	std::string strtime = to_string(t.tm_year + 1900);
	strtime += "_"+to_string(t.tm_mon + 1);
	return  strtime;

}

int main()
{
	std::string strtime=getTime();
	cout << strtime << endl;




	vector<vector<int> > vecTest;
	vector<int> vec_int;

	vec_int.push_back(0);
	vec_int.push_back(1);
	vec_int.push_back(2);
	vec_int.push_back(3);

	vecTest.push_back(vec_int);

	auto iter = vecTest.begin();

	for (int i = 0; i < vec_int.size(); ++i)
	{
		cout << (*iter)[i] << endl;
	}
	
	//string fileName;
	//string section = "finish_model_name";
	//map<string, string>fname;

	//CParseIniFile config;
     //bool wrietr=config.writeConfigToken(L"token");
	
	CFilePath* flek = new CFilePath;

	//flek->GetInitPath();

	//flek->GetInitText();

	flek->GetlogingIsNotUserId();


	//string fileName;
	//string section = "finish_model_name";
	map<string, string>fname;
	CParseIniFile config;
	bool flage = config.ReadConfig("config.ini", fname, "COMMOND");
	if (flage)
	{
		cout << fname["finish_model_name"] << endl;
		cout << fname["client_model_name"] << endl;
		cout << stod(fname["threshold"]) << endl;
	}



	return 0;
}


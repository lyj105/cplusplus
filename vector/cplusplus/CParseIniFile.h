#pragma once
#ifndef _CPARSELNIFILE_H_
#define _CPARSELNIFILE_H_
#define _AFXDLL 
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <afx.h>
#include <windows.h>
#include "WinDef.h"
#include <tchar.h>
#define COMMENT_CHAR '#'
//#include "afxdtctl.h"
using namespace std;

class CParseIniFile
{
public:
	bool writeConfig(wstring accEdit, wstring velEdit);
	bool writeConfigToken(wstring token);
public:
	bool ReadConfig(const string& filename, map<string, string>& mContent, const char* section);
	bool AnalyseLine(const string & line, string & key, string & val);
	void Trim(string & str);
	bool IsSpace(char c);
	bool IsCommentChar(char c);
	void PrintConfig(const map<string, string> & mContent);

public:
	typedef struct _InitText
	{
		wchar_t initTextKey[100];	//键
		int initTextAccount;		//账户
		double volume;				//下单手数
	}InitText;
	InitText mpInitText;
	vector<InitText> vecInitText;
	int iniCount = 0;

};

class CFilePath
{
public:
	CFilePath();
	~CFilePath();
public:
	wstring GetInitPath();
	void GetInitText();
	int GetlogingIsNotUserId();
	std::string WStringToString(const std::wstring &wstr);
	///std::vector<std::wstring> StringSegmentation(std::wstring splitNum);
};
#endif // !1


//设置ini路径到exe同一目录下
#ifndef CONFIG_FILE
#define CONFIG_FILE		(TEXT("AccountCon.ini"))
#endif

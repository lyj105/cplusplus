// MultiByteToWideChar.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

#include <windows.h>

using namespace std;


std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
#include "Wininet.h"

int main()
{

	char sBuf[25] = { 0 };

	strcpy_s(sBuf, "我是下蛋的猫");

	std::string stringo_UTF8 = string_To_UTF8("我是");

	//获取输入缓存大小
	int sBufSize = strlen(sBuf);

	char*  str = &sBuf[0];

	//获取输出缓存大小
	//VC++ 默认使用ANSI，故取第一个参数为CP_ACP
	DWORD dBufSize = MultiByteToWideChar(CP_ACP, 0, sBuf, sBufSize, NULL, 0);
	printf("需要wchar_t%u个\n", dBufSize);

	wchar_t * dBuf = new wchar_t[dBufSize];
	wmemset(dBuf, 0, dBufSize);

	//进行转换
	int nRet = MultiByteToWideChar(CP_ACP, 0, sBuf, sBufSize, dBuf, dBufSize);

	if (nRet <= 0)
	{
		cout << "转换失败" << endl;
		DWORD dwErr = GetLastError();
		switch (dwErr)
		{
		case ERROR_INSUFFICIENT_BUFFER:
			printf("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			printf("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			printf("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			printf("ERROR_NO_UNICODE_TRANSLATION\n");
			break;
		}
	}
	else
	{
		cout << "转换成功" << endl;
		cout << dBuf;
	}

	delete(dBuf);

	
		DWORD   flag;
		bool    con = InternetGetConnectedState(&flag, 0);

}



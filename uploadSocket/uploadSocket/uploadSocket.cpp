// uploadSocket.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<vector>
#include<WinSock2.h>

#include <ws2tcpip.h>
#include <stdio.h>



#include <cstdio>  
#include <fstream>  
#include<string>
#include<io.h>


#pragma comment(lib, "WS2_32.Lib")

using namespace std;


size_t getSize(string path)
{
	FILE * file;
	//file = fopen(path.c_str(), "rb");

	errno_t err;
	// Open for read (will fail if file "crt_fopen_s.c" does not exist)
	err = fopen_s(&file, path.c_str(), "r");
	if (err == 0)
	{
		printf("The file 'crt_fopen_s.c' was opened\n");
	}
	else
	{
		printf("The file 'crt_fopen_s.c' was not opened\n");
	}


	size_t sizeOfPic;

	fseek(file, 0, SEEK_END);   ///将文件指针移动文件结尾  
	sizeOfPic = ftell(file); ///求出当前文件指针距离文件开始的字节数  
	fclose(file);

	return sizeOfPic;
}

void getFiles(std::string path, vector<std::string>& files)
{
	//文件句柄  
	long long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}


int main()
{

	WSADATA wsaData;
	SOCKET sockClient;//客户端Socket  
	SOCKADDR_IN addrServer;//服务端地址  
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//新建客户端socket  
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	//定义要连接的服务端地址  
	//addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//目标IP(127.0.0.1是回送地址)  

	//int inet_pton(int af, const char *src, void *dst);
	PCWSTR src = TEXT("127.0.0.1");
	WCHAR ip[16] = TEXT("0");  //初始化是个好习惯
	struct in_addr dst;

	int i = 0;
	i = InetPton(AF_INET, src, &dst);
	if (1 == i)
	{
		cout << "addr is " << dst.S_un.S_addr << endl;
	}
	//const char *inet_ntop(int af, const void *src, char *dst, socklen_t cnt);
	if (InetNtop(AF_INET, &dst.S_un.S_addr, ip, 100) == NULL)
	{
		cout << "error" << endl;
		return -1;
	}


	//InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &addrServer.sin_addr.s_addr);

	addrServer.sin_addr.S_un.S_addr = dst.S_un.S_addr;//目标IP(127.0.0.1是回送地址)  
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);//连接端口6000  
	//连接到服务端  
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	//发送数据  
	//  char message[20] = "HelloSocket!";  
	char recvBuf[30];
	char size[20];

	string path = "F:\\a";
	vector<string> files;

	getFiles(path, files);

	if (files.size() > 0)
	{
		//发送文件数量
		char file_num[256];
		sprintf_s(file_num, "%d", files.size());
		send(sockClient, file_num, strlen(file_num), 0);
		//服务端确认收到
		int numRecv_size;
		char numBuf[1024];
		numRecv_size = recv(sockClient, numBuf, 1024, 0);
		char* numRecv = new char[numRecv_size + 1];
		for (int i = 0; i < numRecv_size; i++)
			numRecv[i] = numBuf[i];
		numRecv[numRecv_size] = '\0';

		if (strcmp(numRecv, "num_recv") == 0)
		{
			for (auto it = files.begin(); it != files.end(); it++)
			{
				//发送文件名
				size_t pos;
				pos = it->find_last_of("/\\");
				if (pos == string::npos)
				{
					break;
				}
				string file_str = it->substr(pos + 1);
				char file_buf[256];
				sprintf_s(file_buf, "%s", file_str.c_str());
				send(sockClient, file_buf, strlen(file_buf), 0);
				//服务端确认收到
				int nameRecv_size;
				char nameBuf[1024];
				nameRecv_size = recv(sockClient, nameBuf, 1024, 0);
				char* nameRecv = new char[nameRecv_size + 1];
				for (int i = 0; i < nameRecv_size; i++)
				{
					nameRecv[i] = nameBuf[i];
				}
				nameRecv[nameRecv_size] = '\0';

				if (strcmp(nameRecv, "name_recv") != 0)
					break;

				//发送文件大小
				int fileSize = getSize(*it);
				char file_size[256];
				sprintf_s(file_size, "%d", fileSize);
				send(sockClient, file_size, strlen(file_size), 0);
				//服务端确认收到
				int sizeRecv_size;
				char sizeBuf[1024];
				sizeRecv_size = recv(sockClient, sizeBuf, 1024, 0);
				char* sizeRecv = new char[sizeRecv_size + 1];
				for (int i = 0; i < sizeRecv_size; i++)
					sizeRecv[i] = sizeBuf[i];
				sizeRecv[sizeRecv_size] = '\0';
				if (strcmp(sizeRecv, "size_recv") != 0)
					break;

				FILE * file;
				//file = fopen(it->c_str(), "rb");
			    int	err = fopen_s(&file, it->c_str(), "rb");
				if (err == 0)
				{
					printf("The file 'crt_fopen_s.c' was opened\n");
				}
				else
				{
					printf("The file 'crt_fopen_s.c' was not opened\n");
				}

				char buf[1024];
				while (!feof(file))
				{
					memset(buf, 0, sizeof(buf));
					size_t readlen = fread(buf, sizeof(char), sizeof(buf), file);
					send(sockClient, buf, readlen, 0);
				}
				//		send(sockClient, "completed", strlen("completed"), 0);
				fclose(file);
			}
		}



	}

	//关闭socket  
    closesocket(sockClient);
	WSACleanup();
    std::cout << "Hello World!\n"; 
}


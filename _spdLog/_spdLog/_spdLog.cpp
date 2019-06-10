// _spdLog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <cstdio>

#include "spdlog/spdlog.h"
#pragma comment(lib, "lib/spdlog.lib")

bool _GetSubPath(std::string strPath, std::string& strSubPath, int nSearch)
{
	if (-1 == nSearch || strPath.empty())
		return false;
	std::string::size_type nPos1 = std::string::npos;
	nPos1 = strPath.find_last_of("\\");
	if (nPos1 != -1)
	{
		strSubPath = strPath.substr(nPos1 + 1, strPath.length() - nPos1);
		int nNewSearch = nSearch > 1 ? nSearch - 1 : -1;
		_GetSubPath(strPath.substr(0, nPos1), strSubPath, nNewSearch);
	}
	return true;
}
std::string  y_GetSubPath(std::string strPath, std::string& strSubPath, int nSearch)
{

	if (-1 == nSearch || strPath.empty())
		return false;
	std::string::size_type nPos1 = std::string::npos;
	nPos1 = strPath.find_last_of("\\");
	if (nPos1 != -1)
	{
		strSubPath = strPath.substr(nPos1 + 1, strPath.length() - nPos1);
		int nNewSearch = nSearch > 1 ? nSearch - 1 : -1;
		_GetSubPath(strPath.substr(0, nPos1), strSubPath, nNewSearch);
	}
	return strPath;
}


void foo()
{
	// test 1
	std::string str = "d:\\a\\test\\path\\name";
	int pos = str.find_last_of('\\');
	std::string name = str.erase(0, pos + 1);
	std::cout << name << std::endl;
	// test 2
	std::string path = "/this/is/a/test/path/name";
	pos = str.find_last_of('/');
	name = str.erase(0, pos + 1);
	std::cout << name << std::endl;
}
void daily_example();
int main()
{


	std::string strPath = "f:\zentv2.0\zent\branches\spinev1.0\zent\zent\src\zentwindowgui\zentimportdatagui\zentimportpatientdatagui.cpp";
	std::string strSubPath = "";
    std::string  sx= y_GetSubPath(strPath, strSubPath, 1);
	
	foo();
	spdlog::info(sx);

	printf("In file:%s, function:%s() and line:%d", __FILE__, __func__, __LINE__);


	spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	spdlog::warn("Easy padding in numbers like {:08d}", 12);
	spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	spdlog::info("Support for floats {:03.2f}", 1.23456);
	spdlog::info("Positional args are {1} {0}..", "too", "supported");
	spdlog::info("{:>8} aligned, {:<8} aligned", "right", "left");
	spdlog::info("T今天的田阳");
	// Runtime log levels
	spdlog::set_level(spdlog::level::info); // Set global log level to info
	spdlog::debug("()");
	spdlog::set_level(spdlog::level::trace); // Set specific logger's log level
	spdlog::debug("This message should be displayed..");

	// Customize msg format for all loggers
	spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] [thread %t] %v");
	spdlog::info("T423432%%7の钱文09今天的田阳");
	spdlog::set_pattern("%+"); // back to default format


	try
	{

		daily_example();


		// Flush all *registered* loggers using a worker thread every 3 seconds.
		// note: registered loggers *must* be thread safe for this to work correctly!
		spdlog::flush_every(std::chrono::seconds(3));

		// Apply some function on all registered loggers
		spdlog::apply_all([&](std::shared_ptr<spdlog::logger> l) { l->info("End of example今天的田阳."); });

		// Release all spdlog resources, and drop all loggers in the registry.
		// This is optional (only mandatory if using windows + async log).
		spdlog::shutdown();
	}

	// Exceptions will only be thrown upon failed logger or sink construction (not during logging).
	catch (const spdlog::spdlog_ex &ex)
	{
		std::printf("Log initialization failed: %s\n", ex.what());
		return 1;
	}
}

#include "spdlog/sinks/daily_file_sink.h"
void daily_example()
{
	// Create a daily logger - a new file is created every day on 2:30am.
	auto daily_logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 2, 30);
}
#ifndef _COMMON_H
#define _COMMON_H
#ifdef WIN32

#include <winsock2.h>

typedef __int8					int8_t;
typedef __int16					int16_t;
typedef __int32					int32_t;
typedef __int64					int64_t;

typedef unsigned __int8			uint8_t;
typedef unsigned __int16		uint16_t;
typedef unsigned __int32		uint32_t;
typedef unsigned __int64		uint64_t;

#define atoll(_String) \
	_atoi64(_String)
#else
#include <sys/types.h>
//#include <sys/socket.h>
#include <stdint.h>
//#include<linux/string.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
using namespace std;
enum SERVER_ACTION {
	SERVER_STARTNEW = 0,//¿ªÐÂ·þ
};
#ifdef WIN32
#define  PATH_DELIMTER "\\"
#else
#define  PATH_DELIMTER "/"
#endif
#endif
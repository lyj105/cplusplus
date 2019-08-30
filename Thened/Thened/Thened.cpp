// Thened.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <thread>

void geteting() {

	std::cout << "hello thread!" << std::endl;

	return;
}

int main()
{
	std::thread t(geteting);
	t.join();

    std::cout << "Hello World!\n"; 
	return 1;
}

// async.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include <future>
#include <string>
#include <vector>


int mythread()
{
	std::cout << "mythread() start thread id =" << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "mythread() start thread id =" << std::this_thread::get_id() << std::endl;
	return 5;
}

bool is_prime(int x) {
	for (int i = 2; i < x; ++i) if (x%i == 0) return false;
	return true;
}

// 定义一个会返回5的函数
int fun(char c) {

	// 循环输出字符
	for (int i = 0; i < 20; ++i) {
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::microseconds(50));
		//        this_thread::yield();
	}

	return 5;
}



int main()
{
	// call function asynchronously:
	std::future<bool> fut = std::async(is_prime, 700020007);

	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span(100);
	while (fut.wait_for(span) == std::future_status::timeout)
	{
		std::cout << '.';
	}
		

	bool x = fut.get();

	std::cout << "\n700020007 " << (x ? "is" : "is not") << " prime.\n";

	return 0;


}

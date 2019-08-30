// mutex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <mutex>

/**std::mutex 介绍
下面以 std::mutex 为例介绍 C++11 中的互斥量用法。
std::mutex 是C++11 中最基本的互斥量，std::mutex 对象提供了独占所有权的特性——即不支持递归地对 std::mutex 对象上锁，而 std::recursive_lock 则可以递归地对互斥量对象上锁。
std::mutex 的成员函数
构造函数，std::mutex不允许拷贝构造，也不允许 move 拷贝，最初产生的 mutex 对象是处于 unlocked 状态的。
lock()，调用线程将锁住该互斥量。线程调用该函数会发生下面 3 种情况：
(1).如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，直到调用 unlock之前，该线程一直拥有该锁。
(2).如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住。
(3).如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。
unlock()， 解锁，释放对互斥量的所有权。
try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。线程调用该函数也会出现下面 3 种情况；
(1).如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量。
(2).如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉。(3).如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。
下面给出一个与 std::mutex 的小例子
**/



volatile int counter(0);

std::mutex mtx;

void attempt_10k_increases() {

	for (int i=0;i<10000;i++)
	{
		if (mtx.try_lock())
		{
			++counter;
			printf("%d \n", counter);
			mtx.unlock();

		}
	}
}



int main()
{
	std::thread threads[10];
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(attempt_10k_increases);

	for (auto& th : threads) th.join();
	std::cout << counter << " successful increases of the counter.\n";

	return 0;
}



// template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

template <int N>
void counting(std::ostream& os) {
  counting<N - 1>(os);  // *
  os << N << std::endl;
}

template <>
void counting<1>(std::ostream& os) {
  os << 1 << std::endl;
}



int main()
{
	const int N = 10;
	counting<N>(std::cout);

    std::cout << "Hello World!\n"; 
}


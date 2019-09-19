// Thened.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <thread>

#include <thread>
#include <iostream>

#include "stdio.h" 
#include "conio.h"

class CTestWirte
{
public:
	CTestWirte() { this->_dValue = 0.0; }
	~CTestWirte() {}
public:
	static void Run(CTestWirte* pThis, double* pDouble)
	{
		while (*pDouble <= 1.0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			pThis->_dValue += 0.01;
			*pDouble = pThis->_dValue;
		}
	}
protected:
	double _dValue;
};

class Parent

{

public:

	char data[20];
	void Function1();
	virtual void Function2();   // 这里声明Function2是虚函数

}parent;

void Parent::Function1()
{
	printf("This is parent,function1\n");
}

void Parent::Function2()

{
	printf("This is parent,function2\n");
}

class Child :public Parent

{
	void Function1();
	void Function2();

} child;

void Child::Function1()

{
	printf("This is child,function1\n");
}

void Child::Function2()

{
	printf("This is child,function2\n");
}


int main(int argc, char* argv[])
{
	int nMainRet = 0;

#if 0
	CTestWirte test;
	double dValue = 0.0;
	std::thread thread(&CTestWirte::Run, &test, &dValue);
	thread.detach();

	double dTmpValue = dValue;
	while (dValue <= 1.0)
	{
		//if (dTmpValue != dValue)
		//{
		dTmpValue = dValue;
		printf("read> %.5f \n", dTmpValue);
		//	}
	}

#endif
	Parent * p;
	if (_getch() == 'c')     // 如果输入一个小写字母c	
		p = &child;         // 指向继承类对象
	else
		p = &parent;       // 否则指向基类对象
	p->Function1();   // 这里在编译时会直接给出Parent::Function1()的入口地址。	
	p->Function2();    // 注意这里，执行的是哪一个Function2？



	return nMainRet;
}


/*!
/************************************************************************/
/*    用任意版本的Visual C++或Borland C++编译并运行，输入一个小写字母c，得到下面的结果：

This is parent, function1
This is child, function2

为什么会有第一行的结果呢？因为我们是用一个Parent类的指针调用函数Fuction1()，虽然实际上这个指针指向的是Child类的对象，但编译器无法知道这一事实（直到运行的时候，程序才可以根据用户的输入判断出指针指向的对象），它只能按照调用Parent类的函数来理解并编译，所以我们看到了第一行的结果。

那么第二行的结果又是怎么回事呢？我们注意到，Function2()函数在基类中被virtual关键字修饰，也就是说，它是一个虚函数。虚函数最关键的特点是“动态联编”，它可以在运行时判断指针指向的对象，并自动调用相应的函数。
如果我们在运行上面的程序时任意输入一个非c的字符，结果如下：

This is parent, function1
This is parent, function2 ../                                                                  */
/************************************************************************/

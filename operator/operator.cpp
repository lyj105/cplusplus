// operator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#define  _CRT_SECURE_NO_WARNINGS

class operaClassyonG
{
public:
	operaClassyonG() {
	}
	operaClassyonG(const char* pszInputStr)
	{
		pszTestStr = new char[strlen(pszInputStr) + 1];
		//strncpy(pszTestStr, pszTestStr, strlen(pszTestStr) + 1);
		strcpy_s(pszTestStr, strlen(pszInputStr)+1, pszInputStr);
	}
	virtual ~operaClassyonG()
	{
		delete pszTestStr;
	}
	operaClassyonG& operator=(const operaClassyonG& clasQ)
	{
	//// 避免自赋值
		if (this!=&clasQ)
		{
			//避免内存泄露
			if (pszTestStr!=NULL)
			{
				delete pszTestStr;
				pszTestStr = NULL;
			}
			pszTestStr = new char[strlen(clasQ.pszTestStr) + 1];
			strcpy_s(pszTestStr, strlen(clasQ.pszTestStr) + 1, clasQ.pszTestStr);
		}

		return  *this;
	
	}

	//我们修改一下前面出错的代码示例，现编写一个包含赋值运算符重载函数的类，代码（operator

public:
	char* pszTestStr;

};


//上述错误信息说明：当obj1和obj2进行析构的时候，由于重复释放了一块内存，导致程序崩溃报错。在这种情况下，就需要我们重载赋值运算符“ = ”了。

int main()
{
	operaClassyonG obj("iieoeooe");

	operaClassyonG obj2;
	obj2 = obj;

	std::cout << "obj2.pszTestStr is: " << obj2.pszTestStr << std::endl;
	std::cout << "addr(obj1.pszTestStr) is: " << &obj.pszTestStr << std::endl;
	std::cout << "addr(obj2.pszTestStr) is: " << &obj2.pszTestStr << std::endl;
	

    std::cout << "Hello World!\n"; 
}



/** 通过上述结果能够看到，我们利用赋值运算符重载函数，解决了对象赋值的情况下，析构函数中过程中多次释放同一块内存的问题。

对于上述代码，有以下几点需要说明：



当为一个类的对象赋值（可以用本类对象为其赋值，也可以用其它类型的值为其赋值）时，该对象（如本例的obj2）会调用该类的赋值运算符重载函数，进行具体的赋值操作。如上述代码中的“obj2 = obj1; ”语句，用obj1为obj2赋值，则会由obj2调用ClassA类的赋值运算符重载函数。
语句“ClassA obj2;
obj2 = obj1; “
和语句“ClassA obj2 = obj1; ”在调用函数上是有区别的：前者第一句是对象obj2的声明及定义，调用类ClassA的无参构造函数，所以“obj2 = obj1; ”一句是在对象obj2已经存在的情况下，用obj1来为obj2赋值，调用的是赋值运算符重载函数；而后者，是用obj1来初始化obj2，调用的是拷贝构造函数。关于拷贝构造函数的语句样式为“ClassA(const ClassA& cls)”，关于拷贝构造函数的内容，此处不进行详述。
当程序没有显式地提供一个以“本类或本类的引用”为参数的赋值运算符重载函数时，编译器会自动生成一个默认的赋值运算符重载函数。 **/

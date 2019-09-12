// Matrix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "string"
#include "SpacePoint.h"

using namespace std;

int main()
{
	cout << "****************************************" << endl;
	cout << "***           欢迎来到点类           ***" << endl;
	cout << "***1.关于原点中心对称的点的坐标      ***" << endl;
	cout << "***2.关于三个坐标轴对称的点的坐标    ***" << endl;
	cout << "***3.关于三个坐标轴平面对称的点的坐标***" << endl;
	cout << "***4.计算点到点距离                  ***" << endl;
	cout << "***5.计算点到直线距离                ***" << endl;
	cout << "***6.计算点到平面距离                ***" << endl;
	cout << "***7.退出程序                        ***" << endl;
	cout << "****************************************\n" << endl;

	double x;
	double y;
	double z;
	cout << "请输入你要新创造的点的三维坐标：" << endl;
	cin >> x >> y >> z;
	SpacePoint new_point(x, y, z);
	cout << "\n***           新的点诞生了           ***" << endl;
	int flag;
	while (true)
	{
		cout << "\n请选择功能：";
		cin >> flag;
		if (flag == 1)
		{
			//中心对称
			new_point.center_symmetry();
		}
		else if (flag == 2)
		{
			//轴对称
			new_point.axial_symmetry();
		}
		else if (flag == 3)
		{
			//平面对称
			new_point.plane_symmetry();
		}
		else if (flag == 4)
		{
			//点到点距离
			cout << "请输入另一个点的三维坐标：" << endl;
			cin >> x >> y >> z;
			double distance = new_point.to_point(x, y, z);
			cout << "两点之间的距离为：" << distance << endl;
		}
		else if (flag == 5)
		{
			//点到直线距离
			cout << "请输入直线上的两个点：" << endl;
			cin >> x >> y >> z;
			SpacePoint *point1 = new SpacePoint(x, y, z);
			cin >> x >> y >> z;
			SpacePoint *point2 = new SpacePoint(x, y, z);
			double distance = new_point.to_line(point1, point2);
			cout << "点到直线的距离为：" << distance << endl;
		}
		else if (flag == 6)
		{
			//点到平面距离
			double A, B, C;
			cout << "请输入平面上的一个点：" << endl;
			cin >> x >> y >> z;
			SpacePoint *point1 = new SpacePoint(x, y, z);
			cout << "请输入平面的任一法向量参数：" << endl;
			cin >> A >> B >> C;
			double distance = new_point.to_plane(point1, A, B, C);
			cout << "点到平面的距离为：" << distance << endl;
		}
		else if (flag == 7)
		{
			//退出
			cout << "成功退出！" << endl;
			break;
		}
	}
	return 0;


}

#include "pch.h"
#include "SpacePoint.h"
#include <iostream>
#include <math.h>



SpacePoint::SpacePoint()
{
}


SpacePoint::~SpacePoint()
{
}


SpacePoint::SpacePoint(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;

};
void SpacePoint::center_symmetry()
{
	std::cout<< "��(" << x << "," << y << "," << z << ")����ԭ�����ĶԳƵĵ�����꣺\n" << "��(" << -x << "," << -y << "," << -z << ")" << std::endl;

};//���ĶԳ�


void SpacePoint::axial_symmetry() {

	std::cout << "��(" << x << "," << y << "," << z << ")����������ԳƵĵ�����꣺" << std::endl;
	std::cout << "x��  |��(" << x << "," << -y << "," << -z << ")" << std::endl;
	std::cout << "y��  |��(" << -x << "," << y << "," << -z << ")" << std::endl;
	std::cout << "z��  |��(" << -x << "," << -y << "," << z << ")" << std::endl;

}; //��Գ�


void SpacePoint::plane_symmetry()
{
	std::cout << "��(" << x << "," << y << "," << z << ")��������������ƽ��ԳƵĵ�����꣺" << std::endl;
	std::cout << "x_yƽ��  |��(" << x << "," << y << "," << -z << ")" << std::endl;
	std::cout << "x_zƽ��  |��(" << x << "," << -y << "," << z << ")" << std::endl;
	std::cout << "y_zƽ��  |��(" << -x << "," << y << "," << z << ")" << std::endl;


}; //ƽ��Գ�


double  SpacePoint::to_point(double a, double b, double c) {

	double diatance;

	diatance = sqrt((x - a)*(x - a) + (y - b)*(y - b) + (z - c)*(z - c));
	 
	return diatance;

}; //�㵽��ľ���


double  SpacePoint::to_line(SpacePoint* point1, SpacePoint *point2)
{

	double distance;
	double l1 = sqrt((point1->x - point2->x)*(point1->x - point2->x) + (point1->y - point2->y)*(point1->y - point2->y) + (point1->z - point2->z)*(point1->z - point2->z));
	double l2 = sqrt((point1->x - x)*(point1->x - x) + (point1->y - y)*(point1->y - y) + (point1->z - z)*(point1->z - z));
	double l3 = sqrt((x - point2->x)*(x - point2->x) + (y - point2->y)*(y - point2->y) + (z - point2->z)*(z - point2->z));
	double cos = (l1*l1 + l2 * l2 - l3 * l3) / (2 * l1*l2);
	distance = l2 * sqrt(1 - cos * cos);
	return distance;


}; //�㵽ֱ�ߵľ���



double SpacePoint::to_plane(SpacePoint *point1, double A, double B, double C) {
	double distance;
	double D;
	D = -A * point1->x - B * point1->y - C * point1->z;
	distance = abs(A*x + B * y + C * z + D) / sqrt(A*A + B * B + C * C);
	return distance;
};
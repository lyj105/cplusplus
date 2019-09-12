#pragma once


class SpacePoint
{
public:
	SpacePoint();
	~SpacePoint();
	SpacePoint(double a,double b,double c);
	void center_symmetry();//中心对称
	void axial_symmetry(); //轴对称
	void plane_symmetry(); //平面对称
	double  to_point(double a,double b,double c); //点到点的距离
	double  to_line(SpacePoint* point1,SpacePoint *point2); //点到直线的距离
	double to_plane(SpacePoint *point1,double A,double B,double C);


public:
	//三维坐标
	double x;
	double y;
	double z;
};


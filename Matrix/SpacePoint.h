#pragma once


class SpacePoint
{
public:
	SpacePoint();
	~SpacePoint();
	SpacePoint(double a,double b,double c);
	void center_symmetry();//���ĶԳ�
	void axial_symmetry(); //��Գ�
	void plane_symmetry(); //ƽ��Գ�
	double  to_point(double a,double b,double c); //�㵽��ľ���
	double  to_line(SpacePoint* point1,SpacePoint *point2); //�㵽ֱ�ߵľ���
	double to_plane(SpacePoint *point1,double A,double B,double C);


public:
	//��ά����
	double x;
	double y;
	double z;
};


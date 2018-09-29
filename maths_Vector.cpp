#include "maths_Vector.h"

Vector2D::Vector2D(Point2D& _p1, Point2D& _p2)
{
		x = _p2.x - _p1.x;
		y = _p2.y - _p1.y;
}

void Vector2D::define(Point2D& _p1, Point2D& _p2)
{
	x = _p2.x - _p1.x;
	y = _p2.y - _p1.y;
}

//================================
// Distance
//================================
float Vector2D::distTwoParra(const Vector2D& _v, const Point2D& _p1, const Point2D& _p2)
{
	if(!colinear(_v))
		return -1.0f;
	Vector2D l_v = strangePerpendicular();
	Point2D l_point;
	Point2D l_point2 = _p1;
	l_point.intersectionVector2D(l_v, _v, l_point2, _p2);
	l_v.define(l_point, l_point2);
	return l_v.magnitude();
}

Point2D Vector2D::operator+(const Point2D& _p)
{
	return Point2D(_p.x + x, _p.y + y);
};

#include "maths_Point.h"

bool Point2D::intersectionVector2D(const Vector2D& _v1, const Vector2D& _v2, const Point2D& _p1, const Point2D& _p2)
{
	if(_v1.x*_v2.y-_v2.x*_v1.y != 0)
	{
		if(_v1.y != 0)
		{
			y = (-(_p1.x*_v1.y-_p1.y*_v1.x)*_v2.y + (_p2.x*_v2.y-_p2.y*_v2.x)*_v1.y)/(_v1.x*_v2.y-_v2.x*_v1.y);
			x = (_p1.x*_v1.y-_p1.y*_v1.x+_v1.x*y)/_v1.y;
		}
		else
		{
			y = (-(_p2.x*_v2.y-_p2.y*_v2.x)*_v1.y + (_p1.x*_v1.y-_p1.y*_v1.x)*_v2.y)/(_v2.x*_v1.y-_v1.x*_v2.y);
			x = (_p2.x*_v2.y-_p2.y*_v2.x+_v2.x*y)/_v2.y;
		}

		return true;
	}
	else //warning, may create bug
	{
		if((_p1.x == _p2.x) || (_p1.y == _p2.y))
			return false;
		return false;
	}
}

Point2D Point2D::operator+(const Vector2D& _v)
{
	return Point2D(_v.x + x, _v.y + y);
};
#ifndef __Point__
#define __Point__
class Point2D;
#include "maths_Vector.h"
class Point2D
{
public:
	float x, y;
//================================
// Constructor
//================================
	Point2D()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Point2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	};
//================================
// Destructor
//================================
	~Point2D()
	{};
//================================
// ResetAll
//================================
	void resetAll()
	{
		x = 0;
		y = 0;
	};

//================================
// Define
//================================
	void define(float _x, float _y)
	{
		x = _x;
		y = _y;
	};

//================================
// Operator
//================================
	void operator=(const Point2D& _p)
	{
		x = _p.x;
		y = _p.y;
	};

	bool operator==(const Point2D& _p)
	{
		if(_p.x == x)
			if(_p.y == y)
				return true;
		return false;
	};

	bool operator!=(const Point2D& _p)
	{
		return !operator==(_p);
	};

	Point2D operator+(const Point2D& _p)
	{
		Point2D point3;
		point3.x = x + _p.x;
		point3.y = y + _p.y;
		return point3;
	};
	bool operator< (const Point2D& _p) const
	{
		if (x<_p.x)
			return true;
		else if (!(_p.x<x) && y<_p.y)
			return true;
		else
			return false;
	}
	Point2D operator+(const Vector2D& _v);

	Point2D operator*(const float _f)
	{
		Point2D point2;
		point2.x = x * _f;
		point2.y = y * _f;
		return point2;
	};

	Point2D operator-(const Point2D& _p)
	{
		Point2D point3;
		point3.x = x - _p.x;
		point3.y = y - _p.y;
		return point3;
	};

	bool operator>(const float _f)
	{
		if(x>_f && y>_f)
			return true;
		return false;
	};

	bool operator<(const float _f)
	{
		if(x<_f && y<_f)
			return true;
		return false;
	};
//================================
// Intersection Vectors
//================================
	bool intersectionVector2D(const Vector2D& _v1, const Vector2D& _v2, const Point2D& _p1, const Point2D& _p2);
};

#endif //__Point__
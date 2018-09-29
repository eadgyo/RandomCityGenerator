#ifndef __VECTOR__
#define __VECTOR__
#include <cmath>
class Vector2D;
#include "maths_Point.h"
#include "Constant.h"
class Vector2D
{
public:
	float x, y;
//================================
// Constructor
//================================
	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	};

	Vector2D(Point2D& _p1, Point2D& _p2);
//================================
// Destructor
//================================
	~Vector2D()
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

	void define(Point2D& _p1, Point2D& _p2);
//================================
// Magnitude
//================================
	float magnitude()
	{
		return sqrt(x*x+y*y);
	};

	float squareMagnitude()
	{
		return (x*x+y*y);
	};
//================================
// Normalize
//================================
	void normalize()
	{
		float l = magnitude();
		if(l>0)
		{
			(*this) *= (1.0/l);
		}
	}

	Vector2D getNormalize()
	{
		Vector2D l_vec = (*this);
		l_vec.normalize();
		return l_vec;
	};
//================================
// Operators
//================================
	void operator*=(const float _value)
	{
		x *= _value;
		y *= _value;
	};

	Vector2D operator*(const float _value)
	{
		return Vector2D(x*_value, y*_value);
	};

	void operator+=(const Vector2D& _v)
	{
		x += _v.x;
		y += _v.y;
	};

	Vector2D operator+(const Vector2D& _v)
	{
		return Vector2D(x+_v.x, y+_v.y);
	};

	Point2D operator+(const Point2D& _p);

	void operator-=(const Vector2D& _v)
	{
		x -= _v.x;
		y -= _v.y;
	};

	Vector2D operator-(const Vector2D& _v)
	{
		return Vector2D(x-_v.y, y-_v.y);
	};

//================================
// Scalar
//================================
	float scalarProduct(const Vector2D& _v)
	{
		return x*_v.x + y*_v.y;
	};

	float operator*(const Vector2D& _v)
	{
		return x*_v.x + y*_v.y;
	};

	float distTwoParra(const Vector2D& _v, const Point2D& _p1, const Point2D& _p2);

	bool colinear(const Vector2D& _v)
	{
		if(x*_v.y - y*_v.x == 0.0f)
			return true;
		else
			return false;
	};

	Vector2D strangePerpendicular()
	{
		Vector2D l_v;
		if(x == 0.0f)
			l_v.define(1,0);
		else if(y == 0.0f)
			l_v.define(0,1);
		else
			l_v.define(-(y/x),1.0f);
		return l_v;
	};

	Vector2D perpendicular()
	{
		return Vector2D(-y,x);
	};

//==============================
//            Angle
//==============================
	float getAngle(Vector2D& _v)
	{
		float l_fTheta = acos(getNormalize().scalarProduct(_v.getNormalize()));
		return (l_fTheta*180)/PI;
	};
//================================
// Magnitude
//================================
};

#endif
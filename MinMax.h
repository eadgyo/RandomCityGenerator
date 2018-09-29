#ifndef __MINMAX__
#define __MINMAX__
#include "maths_Point.h"

struct MinMax
{
//================================
// Constructor
//================================
	MinMax()
	{
		clear();
	};
//================================
// Destructor
//================================
	~MinMax()
	{};
//================================
// Clear
//================================
	void clear()
	{
		xMin = 0;
		xMax = 0;
		yMin = 0;
		yMax = 0;
	};
//================================
// Define
//================================
	void define(float _x1, float _y1, float _x2, float _y2)
	{
		if(_x1 <= _x2)
		{
			xMax = _x2;
			xMin = _x1;
		}
		else
		{
			xMax = _x1;
			xMin = _x2;
		}

		if(_y1 <= _y2)
		{
			yMax = _y2;
			yMin = _y1;
		}
		else
		{
			yMax = _y1;
			yMin = _y2;
		}
	};
	void define(Point2D& _p1, Point2D& _p2)
	{
		if(_p1.x <= _p2.x)
		{
			xMax = _p2.x;
			xMin = _p1.x;
		}
		else
		{
			xMax = _p1.x;
			xMin = _p2.x;
		}

		if(_p1.y <= _p2.y)
		{
			yMax = _p2.y;
			yMin = _p1.y;
		}
		else
		{
			yMax = _p1.y;
			yMin = _p2.y;
		}
	};

//==============================
//           Compare
//==============================
	bool compareXOnly(Point2D l_p2d)
	{
		if(l_p2d.x >= xMin && l_p2d.x <= xMax)
			if(l_p2d.y >= xMin && l_p2d.y <= xMax)
				return true;
		return false;
	};

//==============================
//          Operator
//==============================
	void operator=(const MinMax& _MinMax)
	{
		xMin = _MinMax.xMin;
		xMax = _MinMax.xMax;
		yMin = _MinMax.yMin;
		yMax = _MinMax.yMax;
	};

//==============================
//          Variables
//==============================
	float xMin, xMax, yMin, yMax;
};
#endif
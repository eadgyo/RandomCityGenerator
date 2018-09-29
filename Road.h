#ifndef __ROAD__
#define __ROAD__
#include "maths_Point.h"
#include "maths_Rectangle.h"
#include <vector>
struct Road;
#include "Form.h"
struct Road: public Form
{
	Road(Point2D* _pP2DRoad, float _fThickness);
	Road();
	~Road();
	void define(Point2D* _pP2DRoad, float _fThickness);
};

#endif

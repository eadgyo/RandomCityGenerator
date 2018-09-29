#include "maths_Rectangle.h"

//================================
// Constructor
//================================
Rectangle::Rectangle()
{
	pointLength.resetAll();
	pointCenter.resetAll();
}

Rectangle::Rectangle(const Rectangle& _Rectangle)
{
	pointLength = _Rectangle.pointLength;
	pointCenter = _Rectangle.pointCenter;
	omega = _Rectangle.omega;
	for(int i=0; i<4; i++)
	{
		pointRectangle[i] = _Rectangle.pointRectangle[i];
	}
}
Rectangle::Rectangle(Point2D& _pointCenter,Point2D& _dist)
{
	pointLength.define(_dist.x,_dist.y);
	pointCenter.define(_pointCenter.x,_pointCenter.y);
	omega = 0.0f;
	pointRectangle[0].define(_pointCenter.x - 0.5f*_dist.x, _pointCenter.y - 0.5f*_dist.y);
	pointRectangle[1].define(_pointCenter.x - 0.5f*_dist.x, _pointCenter.y + 0.5f*_dist.y);
	pointRectangle[2].define(_pointCenter.x + 0.5f*_dist.x, _pointCenter.y + 0.5f*_dist.y);
	pointRectangle[3].define(_pointCenter.x + 0.5f*_dist.x, _pointCenter.y - 0.5f*_dist.y);
}
	
Rectangle::Rectangle(Point2D& _pointCenter,Point2D& _dist, float _omega)
{
	pointLength.define(_dist.x,_dist.y);
	pointCenter.define(_pointCenter.x,_pointCenter.y);
	omega = _omega;
	float tempOmega = (_omega * PI)/180;
	pointRectangle[0].x = (_pointCenter.x - (cos(tempOmega)*0.5f*_dist.x) + (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[0].y = (_pointCenter.y - (sin(tempOmega)*0.5f*_dist.x) - (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[1].x = (_pointCenter.x - (cos(tempOmega)*0.5f*_dist.x) - (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[1].y = (_pointCenter.y - (sin(tempOmega)*0.5f*_dist.x) + (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[2].x = (_pointCenter.x + (cos(tempOmega)*0.5f*_dist.x) - (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[2].y = (_pointCenter.y + (sin(tempOmega)*0.5f*_dist.x) + (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[3].x = (_pointCenter.x + (cos(tempOmega)*0.5f*_dist.x) + (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[3].y = (_pointCenter.y + (sin(tempOmega)*0.5f*_dist.x) - (cos(tempOmega)*0.5f*_dist.y));
}
//================================
// ResetAll
//================================
void Rectangle::resetAll()
{
	for(int i=0; i<4; i++)
	{
		pointRectangle[i].resetAll();
	}
	pointCenter.resetAll();
	pointLength.resetAll();
	omega = 0.0f;

}
//================================
// Define
//================================
void Rectangle::define(Point2D& _pointCenter,Point2D& _dist)
{
	pointLength.define(_dist.x,_dist.y);
	pointCenter.define(_pointCenter.x,_pointCenter.y);
	omega = 0;
	pointRectangle[0].define(_pointCenter.x - 0.5f*_dist.x, _pointCenter.y + 0.5f*_dist.y);
	pointRectangle[1].define(_pointCenter.x + 0.5f*_dist.x, _pointCenter.y + 0.5f*_dist.y);
	pointRectangle[2].define(_pointCenter.x + 0.5f*_dist.x, _pointCenter.y - 0.5f*_dist.y);
	pointRectangle[3].define(_pointCenter.x - 0.5f*_dist.x, _pointCenter.y - 0.5f*_dist.y);
}

void Rectangle::define(Point2D& _pointCenter,Point2D& _dist, float _omega)
{
	pointLength.define(_dist.x,_dist.y);
	pointCenter.define(_pointCenter.x,_pointCenter.y);
	omega = _omega;
	float tempOmega = (_omega * PI)/180;
	pointRectangle[0].x = (_pointCenter.x - (cos(tempOmega)*0.5f*_dist.x) + (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[0].y = (_pointCenter.y - (sin(tempOmega)*0.5f*_dist.x) - (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[1].x = (_pointCenter.x - (cos(tempOmega)*0.5f*_dist.x) - (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[1].y = (_pointCenter.y - (sin(tempOmega)*0.5f*_dist.x) + (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[2].x = (_pointCenter.x + (cos(tempOmega)*0.5f*_dist.x) - (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[2].y = (_pointCenter.y + (sin(tempOmega)*0.5f*_dist.x) + (cos(tempOmega)*0.5f*_dist.y));
	pointRectangle[3].x = (_pointCenter.x + (cos(tempOmega)*0.5f*_dist.x) + (sin(tempOmega)*0.5f*_dist.y));
	pointRectangle[3].y = (_pointCenter.y + (sin(tempOmega)*0.5f*_dist.x) - (cos(tempOmega)*0.5f*_dist.y));
}
//================================
// Collision
//================================
bool Rectangle::collisionDetection(Rectangle& _rectangle, bool _bBorder)
{
	if((omega == 0) && (_rectangle.omega == 0))
	{
		if(_bBorder)
			return collisionNotRotated(_rectangle);
		else
			return (collisionRotated(_rectangle, _bBorder) && _rectangle.collisionRotated(*this, _bBorder));
	}
	else
	{
		return (collisionRotated(_rectangle, _bBorder) && _rectangle.collisionRotated(*this, _bBorder));//search if work with only one
	}
	return false;
}

bool Rectangle::collisionNotRotated(Rectangle& _rectangle)
{
	MinMax l_pointsCompare;

	for(int i = 0; i < 4; i++)//look if there is one point in first Rectangle
	{
		l_pointsCompare.define(pointRectangle[0],pointRectangle[2]);
		if((_rectangle.pointRectangle[i].x >= l_pointsCompare.xMin) && (_rectangle.pointRectangle[i].x <= l_pointsCompare.xMax))
			if((_rectangle.pointRectangle[i].y >= l_pointsCompare.yMin) && (_rectangle.pointRectangle[i].y <=  l_pointsCompare.yMax))
			{
				return true;
			}
	}
	for(int i = 0; i < 4; i++)//look if there is one point in second Rectangle
	{
		l_pointsCompare.define(_rectangle.pointRectangle[0],_rectangle.pointRectangle[2]);
		if((pointRectangle[i].x >= l_pointsCompare.xMin) && (pointRectangle[i].x <= l_pointsCompare.xMax))
			if((pointRectangle[i].y >= l_pointsCompare.yMin) && (pointRectangle[i].y <=  l_pointsCompare.yMax))
			{
				return true;
			}
	}
	return false;
	
}

bool Rectangle::collisionRotated(Rectangle& _rectangle, bool _bBorder)
{
	Vector2D l_vector1;
	Vector2D l_vector2;
	Point2D l_point; 
	MinMax l_compare;

	//Choose one corner, and project
	for(int c=0; c<2; c++)
	{
		if(c==0)
		{
			l_vector1.define(pointRectangle[0],pointRectangle[3]);
			l_vector1.normalize();

			l_vector2.define(l_point,pointRectangle[0]);
			l_compare.xMin = l_compare.xMax = l_vector2.scalarProduct(l_vector1);
			l_vector2.define(l_point,pointRectangle[3]);

			if(l_vector2.scalarProduct(l_vector1) < l_compare.xMin)
				l_compare.xMin = l_vector2.scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.xMax)
				l_compare.xMax = l_vector2.scalarProduct(l_vector1);
		}
		else
		{
			l_vector1.define(pointRectangle[0],pointRectangle[1]);
			l_vector1.normalize();

			l_vector2.define(l_point,pointRectangle[0]);
			l_compare.xMin = l_compare.xMax = l_vector2.scalarProduct(l_vector1);
			l_vector2.define(l_point,pointRectangle[1]);

			if(l_vector2.scalarProduct(l_vector1) < l_compare.xMin)
				l_compare.xMin = l_vector2.scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.xMax)
				l_compare.xMax = l_vector2 .scalarProduct(l_vector1);
		}

		l_vector2.define(l_point,_rectangle.pointRectangle[0]);
		l_compare.yMin = l_compare.yMax = l_vector2.scalarProduct(l_vector1);
		for(int i=1; i<4; i++)
		{
			l_vector2.define(l_point,_rectangle.pointRectangle[i]);
			if(l_vector2 .scalarProduct(l_vector1) < l_compare.yMin)
				l_compare.yMin = l_vector2 .scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.yMax)
				l_compare.yMax = l_vector2 .scalarProduct(l_vector1);
		}
		if(_bBorder)
		{
			if((l_compare.xMax < l_compare.yMin) || (l_compare.xMin > l_compare.yMax))
				return false;
		}
		else
		{
			if((l_compare.xMax <= l_compare.yMin) || (l_compare.xMin >= l_compare.yMax))
				return false;
		}
	}
	return true;
}

bool Rectangle::collisionInsideRotated(Rectangle& _rectangle, bool _bBorder)
{
	Vector2D l_vector1;
	Vector2D l_vector2;
	Point2D l_point; 
	MinMax l_compare;
	for(int c=0; c<2; c++)
	{
		if(c==0)
		{
			l_vector1.define(pointRectangle[0],pointRectangle[3]);
			l_vector1.normalize();

			l_vector2.define(l_point,pointRectangle[0]);
			l_compare.xMin = l_compare.xMax = l_vector2.scalarProduct(l_vector1);
			l_vector2.define(l_point,pointRectangle[3]);

			if(l_vector2.scalarProduct(l_vector1) < l_compare.xMin)
				l_compare.xMin = l_vector2.scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.xMax)
				l_compare.xMax = l_vector2.scalarProduct(l_vector1);
		}
		else
		{
			l_vector1.define(pointRectangle[0],pointRectangle[1]);
			l_vector1.normalize();

			l_vector2.define(l_point,pointRectangle[0]);
			l_compare.xMin = l_compare.xMax = l_vector2.scalarProduct(l_vector1);
			l_vector2.define(l_point,pointRectangle[1]);

			if(l_vector2.scalarProduct(l_vector1) < l_compare.xMin)
				l_compare.xMin = l_vector2.scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.xMax)
				l_compare.xMax = l_vector2.scalarProduct(l_vector1);
		}

		l_vector2.define(l_point,_rectangle.pointRectangle[0]);
		l_compare.yMin = l_compare.yMax = l_vector2.scalarProduct(l_vector1);
		for(int i=1; i<4; i++)
		{
			l_vector2.define(l_point,_rectangle.pointRectangle[i]);
			if(l_vector2 .scalarProduct(l_vector1) < l_compare.yMin)
				l_compare.yMin = l_vector2.scalarProduct(l_vector1);
			else if(l_vector2 .scalarProduct(l_vector1) > l_compare.yMax)
				l_compare.yMax = l_vector2.scalarProduct(l_vector1);
		}
		if(_bBorder)
		{
			if((l_compare.xMax < l_compare.yMin) || (l_compare.xMin > l_compare.yMax) || (l_compare.xMax > l_compare.yMax) || (l_compare.xMin < l_compare.yMin))
				return false;

		}
		else
		{
			if((l_compare.xMax <= l_compare.yMin) || (l_compare.xMin >= l_compare.yMax) || (l_compare.xMax >= l_compare.yMax) || (l_compare.xMin <= l_compare.yMin))
				return false;
		}
	}
}

int Rectangle::collisionInside(Rectangle& _Rectangle2, bool _bBorder)
{
	if(_Rectangle2.collisionInsideRotated((*this),_bBorder))
		return 2;
	else if(collisionInsideRotated(_Rectangle2,_bBorder))
		return 1;
	return 0;
}
/*void Rectangle::displayRectangle(CCLayer *scene)
{
	for(int i=0; i<4; i++)
	{
		Tools::createSquare(scene, pointRectangle[i],1);
	}
}*/



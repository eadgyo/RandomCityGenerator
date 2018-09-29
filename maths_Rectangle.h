#ifndef __Rectangle__
#define __Rectangle__
struct Rectangle;
#include "maths_Point.h"
#include "Constant.h"
#include "MinMax.h"

struct Rectangle
{
//================================
// Constructor
//================================
	Rectangle();

	Rectangle(const Rectangle& _Rectangle);

	Rectangle(Point2D& _center,Point2D& _dist);

	Rectangle(Point2D& _center,Point2D& _dist, float _omega);
//================================
// Destructor
//================================
	~Rectangle()
	{};
//================================
// ResetAll
//================================
	void resetAll();
//================================
// Define
//================================
	void define(Point2D& _center,Point2D& _dist);

	void define(Point2D& _center,Point2D& _dist, float _omega);

//================================
// Collision
//================================
	bool collisionDetection(Rectangle& _Rectangle2, bool _bBorder);

	bool collisionNotRotated(Rectangle& _Rectangle2);

	bool collisionRotated(Rectangle& _Rectangle2, bool _bBorder);

	bool collisionInsideRotated(Rectangle& _rectangle, bool _bBorder);

	int collisionInside(Rectangle& _Rectangle2, bool _bBorder);
	
	//void displayRectangle(CCLayer *_scene);
//================================
// Variable
//================================
	Point2D pointRectangle[4];
	Point2D pointCenter;
	Point2D pointLength;

	float omega;
};
#endif //__Rectangle__


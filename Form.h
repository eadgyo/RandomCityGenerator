#ifndef __Form__
#define __Form__
#include "maths_Point.h"
#include "maths_Vector.h"
#include "tools.h"
struct Form
{
//==============================
//        Constructeur
//==============================
	Form()
	{};

//==============================
//         Destructeur
//==============================
	~Form()
	{};

//==============================
//           Getter
//==============================
	Point2D* getMiddlePoints();//Return 4 middle points
	Vector2D* getVector();
	Point2D getCenter();
	float distMin(Form& _Form);
//==============================
//           Drawer
//==============================
	void drawForm(string *aString);

//==============================
//          Variables
//==============================
	Point2D aPoints[4];
};
#endif
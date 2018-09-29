#include "Form.h"
//==============================
//           Getter
//==============================
Point2D* Form::getMiddlePoints()
{
	Point2D* l_pP2D = new Point2D[4];
	l_pP2D[0] = (aPoints[0] + aPoints[1])*0.5f;
	l_pP2D[1] = (aPoints[1] + aPoints[2])*0.5f;
	l_pP2D[2] = (aPoints[2] + aPoints[3])*0.5f;
	l_pP2D[3] = (aPoints[3] + aPoints[0])*0.5f;

	return l_pP2D;
}

Vector2D* Form::getVector()
{
	Vector2D* l_pVec = new Vector2D[4];
	for(int i=0; i<4; i++)
	{
		l_pVec[i].define(aPoints[i], aPoints[(i+1)%4]);
	}
	return l_pVec;
}

Point2D Form::getCenter()
{
	Point2D* l_pp2d = getMiddlePoints();
	Point2D l_center;
	Vector2D l_vec1, l_vec2;
	l_vec1.define(l_pp2d[0], l_pp2d[2]);
	l_vec2.define(l_pp2d[1], l_pp2d[3]);
	l_center.intersectionVector2D(l_vec1, l_vec2, l_pp2d[0], l_pp2d[1]);
	delete [] l_pp2d;
	return l_center;
}

float Form::distMin(Form& _Form)
{
	float l_fdistMin = FLT_MAX;
	Vector2D l_vec;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			l_vec.define(aPoints[i], _Form.aPoints[j]);
			if(l_vec.magnitude() < l_fdistMin)
				l_fdistMin = l_vec.magnitude();
		}
	}
	return l_fdistMin;
}
//==============================
//           Drawer
//==============================
void Form::drawForm(string *aString)
{
	//variables
	Vector2D l_vec;
	Point2D l_point;

	for(int i=0; i<4; i++)
	{
		l_vec.define(aPoints[i],aPoints[(i+1)%4]);
		float maxp = max(abs(l_vec.x),abs(l_vec.y));
		for(int j=0; j<maxp; j++)
		{
			l_point.define(int((l_vec.y*j/maxp) + aPoints[i].y + 0.5) + BLOCK_SIZE/2, int((l_vec.x*j/maxp) + aPoints[i].x + 0.5) + BLOCK_SIZE/2);
			if(l_point < BLOCK_SIZE && l_point > 0)
			{
				char buf[2];
				sprintf_s(buf, "%d", (j%9));
				aString[int(l_point.x)][int(l_point.y)] = buf[0];
			}
		}
	}
}
#include "Road.h"

Road::Road(Point2D* _pP2DRoad, float _fThickness):Form()
{
	Vector2D l_vec1(_pP2DRoad[2], _pP2DRoad[0]);
	Vector2D l_vec2(_pP2DRoad[3], _pP2DRoad[1]);
	l_vec1.normalize();
	l_vec2.normalize();
		
	Form::aPoints[0] = _pP2DRoad[1] + (l_vec1.perpendicular() * (0.5f * _fThickness));
	Form::aPoints[1] = _pP2DRoad[1] + (l_vec1.perpendicular() * ((-0.5f) * _fThickness));
	Form::aPoints[2] = _pP2DRoad[2] + (l_vec2.perpendicular() * ((-0.5f) * _fThickness));
	Form::aPoints[3] = _pP2DRoad[2] + (l_vec2.perpendicular() * (0.5f * _fThickness));
}

Road::Road():Form()
{
}

Road::~Road()
{
	Form::~Form();
}

void Road::define(Point2D* _pP2DRoad, float _fThickness)
{
	Vector2D l_vec1(_pP2DRoad[2], _pP2DRoad[0]);
	Vector2D l_vec2(_pP2DRoad[3], _pP2DRoad[1]);
	l_vec1.normalize();
	l_vec2.normalize();
		
	Form::aPoints[0] = _pP2DRoad[1] + (l_vec1.perpendicular() * (0.5f * _fThickness));
	Form::aPoints[1] = _pP2DRoad[1] + (l_vec1.perpendicular() * ((-0.5f) * _fThickness));
	Form::aPoints[2] = _pP2DRoad[2] + (l_vec2.perpendicular() * ((-0.5f) * _fThickness));
	Form::aPoints[3] = _pP2DRoad[2] + (l_vec2.perpendicular() * (0.5f * _fThickness));
}


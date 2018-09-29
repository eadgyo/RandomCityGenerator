#ifndef __MAPCREATION__
#define __MAPCREATION__

#include "maths_Rectangle.h"
#include "tools.h"
#include "Road.h"
#include <vector>
#include <map>
#include "AdvancedForm.h"

class MapCreation
{
public:
//==============================
//        Constructeur
//==============================
	MapCreation();

//==============================
//         Destructeur
//==============================
	~MapCreation();

//==============================
//           Create
//==============================
	void create();

//==============================
//           Level_4
//==============================
	void createLevel4(AForm* _pAForm);
	void createLevel4RNG(Point2D& _p2DScalair, Point2D& _p2DDistMax, float& _fOmega, Point2D& _p2DlastOmega, float& _fLength, int& _iNbTimes);
	void createLevel4FormRoad(AForm*_pAForm, Point2D** _aPoints);

//==============================
//           Level_X
//==============================
	void createLevelX(AForm* _pAForm);

private:
	int MAXR;

};
#endif
#include "MapCreation.h"

using namespace Tools;
//==============================
//        Constructeur
//==============================
MapCreation::MapCreation()
{
}

//==============================
//         Destructeur
//==============================
MapCreation::~MapCreation()
{
}

//==============================
//           Create
//==============================
void MapCreation::create()
{
	//variable
	MAXR = Tools::rng(10,15);
	AForm* l_pAFormLV4 = new AForm[MAXR];

	createLevel4(l_pAFormLV4);
	createLevelX(l_pAFormLV4);
}

//==============================
//           Level_4
//==============================
void MapCreation::createLevel4(AForm* _pAForm)
{
	//variables
	float l_fOmega, l_fLength;//road angle and length
	int* l_aNbTimes = new int[MAXR];
	Point2D* l_aOmega = new Point2D[MAXR];
	Point2D** l_aPoints = new Point2D*[MAXR];
	for(int i=0; i<MAXR; i++)
	{
		l_aPoints[i] = new Point2D[MAXL + 3];
	}
	Vector2D l_vec1, l_vec2;

	//create points
	//create random omega and random length
	for(int i=0; i<MAXR; i++)
	{
		l_fOmega = (float(2*PI)/MAXR) * i + (rng(0,20)- 10.0f)*0.01f;
		
		//set first road segment angle 
		l_aOmega[i].x = (float(2*PI)/MAXR) * i;
		l_aOmega[i].y = l_fOmega;
		l_aNbTimes[i] = 0;
		
		//create road points
		for(int j=1; j<MAXL + 3; j++)
		{
			//get proj of road on normal road
			l_vec1.define(l_aPoints[i][j-1], Point2D());
			l_vec2.define(Point2D(cos((float(2*PI)/MAXR) * i), sin((float(2*PI)/MAXR) * i)), Point2D());
			l_vec2.normalize();
			Point2D l_p2DScalair(l_vec1.scalarProduct(l_vec2), l_vec1.scalarProduct(l_vec2.perpendicular()));

			//get proj of road on last road
			float tempOmega = (float(2*PI)/MAXR) * (i-1);
			l_vec1.define(Point2D((j-1)*cos(tempOmega) , (j-1)*sin(tempOmega)), Point2D());
			l_vec2.define(Point2D(cos((float(2*PI)/MAXR) * i) , sin((float(2*PI)/MAXR) * i)), Point2D());
			l_vec2.normalize();
			Point2D l_p2DDistMax(l_vec1.scalarProduct(l_vec2), l_vec1.scalarProduct(l_vec2.perpendicular()));
			
			//RNG
			createLevel4RNG(l_p2DScalair, l_p2DDistMax, l_fOmega, l_aOmega[i], l_fLength,
				l_aNbTimes[i]);
			
			//create point
			if(j != 1)
			{
				l_aPoints[i][j].define(l_aPoints[i][j-1].x + l_fLength * cos(l_fOmega),
						l_aPoints[i][j-1].y + l_fLength * sin(l_fOmega));
			}
			else
			{
				l_aPoints[i][j].define(20*cos(l_fOmega),
						20*sin(l_fOmega));
			}
		}
	}

	//create Form
	createLevel4FormRoad(_pAForm, l_aPoints);

	delete [] l_aNbTimes;
	delete [] l_aOmega;
	for(int i=0; i<MAXR; i++)
	{
		delete[] l_aPoints[i];
	}
}
void MapCreation::createLevel4RNG(Point2D& _p2DScalair, Point2D& _p2DDistMax, float& _fOmega, 
									 Point2D& _p2DlastOmega, float& _fLength, int& _iNbTimes)
{
	//variable
	const float l_fDist = LENGTH_BIG_FORM;//length in pixels
	float l_fDiff = (_p2DlastOmega.x - _p2DlastOmega.y);

	//create new random road length and correct trajectory
	if(_p2DScalair.x > _p2DDistMax.x * 0.5)
		_fLength = l_fDist*(1 - 0.4f);
	else if(_p2DScalair.x < - _p2DDistMax.x * 0.5)
		_fLength = l_fDist*(1 + 0.4f);
	else
		_fLength = l_fDist + rng(0,4) - 2.0f;

	//create new random road angle and correct trajectory
	if(abs(_p2DScalair.y) > abs(_p2DDistMax.y) * 0.75 && l_fDiff != 0 )
	{
		_fOmega =  _p2DlastOmega.y + l_fDiff;
		_iNbTimes = 0;

	}
	else//angle rng
	{
		if(_iNbTimes > 2 && rng(0,1)==1)
		{
			int l_iRng = rng(0,6);
			
			_fOmega = _p2DlastOmega.y + float((l_iRng - 3.0f)*12*PI)/180;
			if(l_iRng != 3)//in case of no modification
			{
				_iNbTimes = 0;
			}
		}
		else
		{
			_fOmega = _p2DlastOmega.y;
			_iNbTimes++;
		}	
	}
	_p2DlastOmega.y = _fOmega;
}
void MapCreation::createLevel4FormRoad(AForm*_pAForm, Point2D** _aPoints)
{
	//variables
	Point2D l_aP2DRoad[4];
	AForm l_Form;

	//create Road
	for(int i=0; i<MAXR; i++)
	{
		for(int j=0; j<MAXL; j++)
		{
			l_aP2DRoad[0] = _aPoints[i][j];
			l_aP2DRoad[1] = _aPoints[i][j+1];
			l_aP2DRoad[2] = _aPoints[i][j+2];
			l_aP2DRoad[3] = _aPoints[i][j+3];
			_pAForm[i].vecRoad.push_back(Road(l_aP2DRoad, LENGTH_BIG_ROAD));//create road in a row
				
			l_aP2DRoad[0] = _aPoints[i][j];
			l_aP2DRoad[1] = _aPoints[(i+1)%MAXR][j];
			l_aP2DRoad[2] = _aPoints[(i+2)%MAXR][j];
			l_aP2DRoad[3] = _aPoints[(i+3)%MAXR][j];
			_pAForm[i].vecRoad.push_back(Road(l_aP2DRoad, LENGTH_BIG_ROAD));
		}
	}

	//create Form between Road
	for(int i=0; i<MAXR; i++)
	{
		for(int j=0; j<MAXL; j++)
		{
			l_Form.aPoints[0] = _aPoints[i][j];
			l_Form.aPoints[1] = _aPoints[i][j+1];
			l_Form.aPoints[2] = _aPoints[(i+1)%MAXR][j+1];
			l_Form.aPoints[3] = _aPoints[(i+1)%MAXR][j];
			if(l_Form.shorten(LENGTH_BIG_ROAD))
				_pAForm[i].vecForm.push_back(l_Form);
		}
	}
}

//==============================
//           Level_X
//==============================
void MapCreation::createLevelX(AForm*_pAForm)
{
	/*AForm l_AForm;
	l_AForm.aPoints[0].define(500,500);
	l_AForm.aPoints[1].define(450,-150);
	l_AForm.aPoints[2].define(-250,-400);
	l_AForm.aPoints[3].define(-250,300);

	l_AForm.multiSubdivise(1, 5);*/
	string *aString = new string[BLOCK_SIZE];
	for(int i=0; i<BLOCK_SIZE; i++)
	{
		for(int j=0; j<BLOCK_SIZE; j++)
			aString[i].push_back('-');
	}
	
	//l_AForm.drawFormMultiple(aString);
	//l_AForm.vecForm[1].drawFormMultiple(aString);
	//l_AForm.vecForm[2].drawFormMultiple(aString);
	
	//l_AForm.vecForm[0].drawFormMultiple(aString);
	MainResidence l_mainResidence;
	for(int i=0; i<MAXR; i++)
	{
		Residence l_residence0;
		l_residence0.createRng(0, MAXL);
		for(int j=1; j< _pAForm[i].vecForm.size(); j++)
		{
			Residence l_residence;
			l_residence.createRng(l_residence0, 1);
			_pAForm[i].vecForm[j].multiSubdiviseBuilding(LEVEL_MAX - 1, 2, 0.3f, l_residence, l_mainResidence);
			_pAForm[i].vecForm[j].drawFormMultiple(aString);
		}
	}
	Tools::draw(aString);
}


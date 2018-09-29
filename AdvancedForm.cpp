#include "AdvancedForm.h"
//==============================
//        Constructeur
//==============================
void AForm::reset()
{
	sName = "-";
	vecForm.clear();
	vecRoad.clear();
}

//==============================
//           Shorten
//==============================
bool AForm::shorten(float _fLength)
{
	if(!shortenPossible(_fLength))
		return false;

	Vector2D aVec[4];
	for(int i=0; i<4; i++)
	{
		aVec[i].define(aPoints[i],aPoints[(i+1)%4]);
		aVec[i].normalize();
	}
	for(int i=0; i<4; i++)
	{
		Vector2D l_vec = aVec[i].perpendicular() + aVec[(i+1)%4].perpendicular();
		l_vec.normalize();
		aPoints[(i+1)%4] = l_vec*(_fLength)  + aPoints[(i+1)%4] ;
	}
	return true;
}

AForm AForm::getShorten(float _fLength)
{
	AForm l_AForm;
	Vector2D aVec[4];
	for(int i=0; i<4; i++)
	{
		aVec[i].define(aPoints[i],aPoints[(i+1)%4]);
		aVec[i].normalize();
	}
	for(int i=0; i<4; i++)
	{
		Vector2D l_vec = aVec[i].perpendicular() + aVec[(i+1)%4].perpendicular();
		l_vec.normalize();
		l_AForm.aPoints[(i+1)%4] = l_vec*(_fLength)  + aPoints[(i+1)%4] ;
	}
	return l_AForm;
}

bool AForm::shortenPossible(float _fLength)
{
	Vector2D aVec[4];
	for(int i=0; i<4; i++)
	{
		aVec[i].define(aPoints[i],aPoints[(i+1)%4]);
		if(aVec[i].magnitude() < _fLength * 2)
			return false;
	}
	return true;
}

//==============================
//     Correct_Subdivision
//==============================
void AForm::correctAForm(AForm& _AForm1, AForm& _AForm2)
{
	//variables
	Vector2D* l_pVec = getVector();
	Point2D l_projection;
	float l_fLength, l_maxOmega;
	int n1, n2, point, factor, i;
	int l_iCorNeces = correctNecessary(l_pVec);
	if(l_iCorNeces != 0)
	{
		bool l_bX = bool((l_iCorNeces)%2);
		i = -1;
		l_maxOmega = 100;
		for(int j=0; j<4; j++)//seek for max
		{
			float l_fOmega = l_pVec[j].getAngle(l_pVec[(j+1)%4]);
			if(l_fOmega > l_maxOmega)
			{
				i = j;
			}
		}
	
		if(i != -1)//create a triangle
		{
			AForm l_AForm;
			correctVec(l_bX, i, n1, n2, factor, l_AForm);
			l_fLength =  l_pVec[n1].getNormalize().scalarProduct(l_pVec[n2]);

			if(l_fLength < - l_pVec[n1].magnitude() * 0.25f)
				l_fLength = l_pVec[n1].magnitude()* -factor * 0.25f;
			else
				l_fLength = factor * l_fLength;
			
			//correct points
			l_projection = (l_pVec[n1].getNormalize() * l_fLength) + aPoints[(i+1)%4];
			correctPoint(l_bX, _AForm1, _AForm2, l_projection, i);
			l_AForm.aPoints[3] = l_projection;

			l_AForm.bSub = false;
			vecForm.push_back(l_AForm);
		}
	}
	delete [] l_pVec;
}

void AForm::correctVec(bool _bX, int _i, int& _n1, int& _n2, int& _factor, AForm& _AForm)
{
	if(_bX)
	{
		if(_i == 0)
		{
			_factor = 1;
			_n1 = 0;
			_n2 = 1;
			_AForm.aPoints[0] = aPoints[1];
			_AForm.aPoints[1] = aPoints[1];
			_AForm.aPoints[2] = aPoints[2];
		}
		else if(_i == 1)
		{
			_factor = -1;
			_n1 = 2;
			_n2 = 1;
			_AForm.aPoints[0] = aPoints[1];
			_AForm.aPoints[1] = aPoints[1];
			_AForm.aPoints[2] = aPoints[2];
		}
		else if(_i == 2)
		{
			_factor = 1;
			_n1 = 2;
			_n2 = 3;
			_AForm.aPoints[0] = aPoints[0];
			_AForm.aPoints[1] = aPoints[0];
			_AForm.aPoints[2] = aPoints[3];
		}
		else
		{
			_factor = -1;
			_n1 = 0;
			_n2 = 3;
			_AForm.aPoints[0] = aPoints[0];
			_AForm.aPoints[1] = aPoints[0];
			_AForm.aPoints[2] = aPoints[3];
		}
				
	}
	else
	{
		if(_i==0)
		{
			_factor = -1;
			_n1 = 1;
			_n2 = 0;
			_AForm.aPoints[0] = aPoints[0];
			_AForm.aPoints[1] = aPoints[0];
			_AForm.aPoints[2] = aPoints[1];
		}
		else if(_i == 1)
		{
			_factor = 1;
			_n1 = 1;
			_n2 = 2;
			_AForm.aPoints[0] = aPoints[2];
			_AForm.aPoints[1] = aPoints[2];
			_AForm.aPoints[2] = aPoints[3];
		}
		else if(_i == 2)
		{
			_factor = -1;
			_n1 = 3;
			_n2 = 2;
			_AForm.aPoints[0] = aPoints[2];
			_AForm.aPoints[1] = aPoints[2];
			_AForm.aPoints[2] = aPoints[3];
		}
		else
		{
			_factor = 1;
			_n1 = 3;
			_n2 = 0;
			_AForm.aPoints[0] = aPoints[0];
			_AForm.aPoints[1] = aPoints[0];
			_AForm.aPoints[2] = aPoints[1];
		}
	}
}

void AForm::correctPoint(bool _bX, AForm& _AForm1, AForm& _AForm2, Point2D& _projection , int _i)
{
	if(_bX)
	{
		if(_i == 0)
			_AForm2.aPoints[0] = _projection;
		else if(_i == 1)
			_AForm2.aPoints[3] = _projection;
		else if(_i == 2)
			_AForm1.aPoints[3] = _projection;
		else
			_AForm1.aPoints[0] = _projection;
	}
	else
	{
		if(_i == 0)
			_AForm1.aPoints[3] = _projection;
		else if(_i == 1)
			_AForm2.aPoints[3] = _projection;
		else if(_i == 2)
			_AForm2.aPoints[0] = _projection;
		else
			_AForm1.aPoints[0] = _projection;
	}
}

int AForm::correctNecessary(Vector2D* _pVec)
{
	MinMax l_minMax;
	l_minMax.define(_pVec[0].magnitude(),_pVec[1].magnitude(),
		_pVec[2].magnitude(),_pVec[3].magnitude());

	if(l_minMax.xMin > 4 * l_minMax.yMax && l_minMax.xMin < 8 * LENGTH_MIN)
		return 1;

	if(l_minMax.yMin > 4 * l_minMax.xMax && l_minMax.yMin < 8 * LENGTH_MIN)
		return 2;

	return 0;
}

//==============================
//         Subdivision
//==============================
bool AForm::subdivise(bool _bX, float _fmin, float _fdist)
{
	//variables
	Point2D l_p2DMagnitude, l_Point2D;
	Vector2D l_vec1, l_vec2;
	Road l_Road;
	float l_rng, l_rng2;
	AForm l_aAForm[2];
	Point2D point0;
	Point2D point1;

	create2AForms(_bX, l_aAForm[0], l_aAForm[1]);
	subdiviseCreateVec(_bX, l_vec1, l_vec2);
	if(l_vec1.magnitude() < _fmin + _fdist || l_vec2.magnitude() < _fmin + _fdist || _fmin < 0 || _fdist < 0)
		return false;
	else
		reset();
	//correct 
	correctAForm(l_aAForm[0], l_aAForm[1]);

	l_vec1.define(l_aAForm[0].aPoints[0] , l_aAForm[1].aPoints[0]);
	l_vec2.define(l_aAForm[1].aPoints[3] , l_aAForm[0].aPoints[3]);
	point0 = l_aAForm[0].aPoints[0];
	point1 = l_aAForm[1].aPoints[3];

	//create 1 road and 2 AForms
	l_rng = (1.0 + Tools::rng(0,6)*0.01f - 3*0.01f) * 0.5f;
	//l_rng = 0.5f;
	l_Point2D = (l_vec1.getNormalize() * (l_vec1.magnitude() * l_rng - _fdist)) + point0;
	l_aAForm[0].aPoints[1] = l_Point2D;
	l_Road.aPoints[0] = l_Point2D;

	l_Point2D = (l_vec1.getNormalize() * (l_vec1.magnitude() * l_rng + _fdist)) + point0;
	l_aAForm[1].aPoints[1] = l_Point2D;
	l_Road.aPoints[1] = l_Point2D;

	//l_rng2 = aRng(l_rng, l_vec1, l_vec2);//get correction on rng
	l_rng2 = (1.0 + Tools::rng(0,6)*0.01f - 3*0.01f) * 0.5f;
	l_Point2D = (l_vec2.getNormalize() * (l_vec2.magnitude() * l_rng2 + _fdist)) + point1;
	l_aAForm[0].aPoints[2] = l_Point2D;
	l_Road.aPoints[3] = l_Point2D;

	l_Point2D = (l_vec2.getNormalize() * (l_vec2.magnitude() *  l_rng2 - _fdist)) + point1;
	l_aAForm[1].aPoints[2] = l_Point2D;
	l_Road.aPoints[2] = l_Point2D;

	vecForm.push_back(l_aAForm[0]);
	vecForm.push_back(l_aAForm[1]);
		
	vecRoad.push_back(l_Road);

	return true;
}

float AForm::aRng(float _fRng, Vector2D& _vec1, Vector2D& _vec2)
{
	//variables
	float l_theta, l_rng;
	Point2D l_p2DMiddle1, l_p2DMiddle2;
	Vector2D l_vec;

	l_p2DMiddle1 = (_vec1 * _fRng) + aPoints[0];
	l_p2DMiddle2.intersectionVector2D(_vec1.getNormalize().perpendicular(), _vec2.getNormalize(), l_p2DMiddle1, aPoints[2]);
	l_vec.define(l_p2DMiddle2, l_p2DMiddle1);
	l_vec.normalize();
	l_theta = (acos((l_vec).scalarProduct(_vec2.getNormalize()))*180)/PI;//determine angle
	if(l_theta > 105|| l_theta < 75)
	{
		l_vec.define(aPoints[2], l_p2DMiddle2);
		l_rng = l_vec.magnitude()/_vec2.magnitude();
		if(l_rng < 0.3f || l_rng > 0.7f)
			l_rng = 0.5f;
	}
	else
	{
		l_vec.define(aPoints[2], l_p2DMiddle2);
		l_rng = l_vec.magnitude()/_vec2.magnitude() + Tools::rng(0,6)*0.008f - 3*0.008f;
		if(l_rng < 0.3f || l_rng > 0.7f)
			l_rng = (1.0 + Tools::rng(0,6)*0.01f - 3*0.01f) * 0.5f;
	}
	return l_rng;
}

void AForm::create2AForms(bool _bX, AForm& l_AForm1, AForm& l_AForm2)
{
	if(_bX)
	{
		l_AForm1.aPoints[0] = aPoints[0];
		l_AForm1.aPoints[3] = aPoints[3];
		l_AForm2.aPoints[0] = aPoints[1];
		l_AForm2.aPoints[3] = aPoints[2];
	}
	else
	{
		l_AForm1.aPoints[0] = aPoints[0];
		l_AForm1.aPoints[3] = aPoints[1];
		l_AForm2.aPoints[0] = aPoints[3];
		l_AForm2.aPoints[3] = aPoints[2];
	}

}

void AForm::subdiviseCreateVec(bool _bX, Vector2D& _vec1, Vector2D& _vec2)
{
	if(_bX)
	{
		_vec1.define(aPoints[0], aPoints[1]);
		_vec2.define(aPoints[2], aPoints[3]);
	}
	else
	{
		_vec1.define(aPoints[0], aPoints[3]);
		_vec2.define(aPoints[2], aPoints[1]);
	}
}


//==============================
//       Multi_Subdivise
//==============================
void AForm::multiSubdivise(int _n, float _fThickness)
{
	if(bSub && _n>0 && subdivise(bool(_n%2), _fThickness * 2, _fThickness))
	{
		for(int i=0; i<vecForm.size(); i++)
		{
			if(vecForm[i].bSub)
				vecForm[i].multiSubdivise(_n-1, _fThickness);
		}
	}
};

void AForm::multiSubdiviseBuilding(int _n, float _fThickness, float _fDeltaThickness, Residence& _residence, MainResidence& _mainResidence)
{
	int n = _n;
	if(n>0)
	{
		if(getLengthMin().x < int(LENGTH_MIN + Tools::rng(0,RNG_LENTH)))
			if(getLengthMin().y < int(LENGTH_MIN + Tools::rng(0,RNG_LENTH)))
				return;
		bool bSide;
		if(getLengthMin().x < (_n-1)*LENGTH_MIN*1.75f)
			bSide = false;
		else if(getLengthMin().y < (_n-1)*LENGTH_MIN)
			bSide = true;
		else
		{
			bSide = bool(_n%2);
			n--;
		}
		if(subdivise(bSide, LENGTH_MIN, _fThickness))
		{
			for(int i=0; i<vecForm.size(); i++)
			{		
				if(!_residence.createBuilding(vecForm[i], _mainResidence) && vecForm[i].bSub)
				{
					Residence l_residence;
					l_residence.createRng(_residence, LEVEL_MAX - _n);
					
					if(_fThickness < 3*_fDeltaThickness)
						vecForm[i].multiSubdiviseBuilding(min(5,n), 0, 0, l_residence, _mainResidence);
					else
						vecForm[i].multiSubdiviseBuilding(n, _fThickness - _fDeltaThickness, _fDeltaThickness, l_residence, _mainResidence);
				}
			}
		}
		else if(subdivise(!bSide, LENGTH_MIN, _fThickness))
		{
			for(int i=0; i<vecForm.size(); i++)
			{
				if(!_residence.createBuilding(vecForm[i], _mainResidence) && vecForm[i].bSub)
				{
					Residence l_residence;
					l_residence.createRng(_residence, LEVEL_MAX - _n);
					vecForm[i].multiSubdiviseBuilding(min(5,n), 0, 0, l_residence, _mainResidence);
				}
			}
		}
	}
}

//==============================
//          Operator
//==============================
//get form between two forms
AForm AForm::operator%(AForm& _AForm)
{
	//variables
	Point2D* l_pP2DMiddlePoints1;
	Point2D* l_pP2DMiddlePoints2;
	Point2D l_p2DSide;
	Vector2D l_vec;
	AForm l_AForm;
	float l_fMinMagnitude = INT_MAX;

	//get 4 Middle Points
	l_pP2DMiddlePoints1 = getMiddlePoints();
	l_pP2DMiddlePoints2 = _AForm.getMiddlePoints();

	//select two sides
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			l_vec.define(l_pP2DMiddlePoints1[i], l_pP2DMiddlePoints2[j]);
			if(l_vec.magnitude() < l_fMinMagnitude)
			{
				l_p2DSide.define(i,j);
				l_fMinMagnitude = l_vec.magnitude();
			}
		}
	}

	//create form
	l_AForm.aPoints[0] = aPoints[int(l_p2DSide.x)];
	l_AForm.aPoints[1] = aPoints[int(l_p2DSide.x + 1)%4];
	l_AForm.aPoints[2] = _AForm.aPoints[int(l_p2DSide.y + 1)%4];
	l_AForm.aPoints[3] = _AForm.aPoints[int(l_p2DSide.y)];

	delete [] l_pP2DMiddlePoints1;
	delete [] l_pP2DMiddlePoints2;
	return l_AForm;
};

void AForm::operator=(const AForm& _AForm)
{
	reset();
	for(int i=0; i<4; i++)
	{
		aPoints[i] = _AForm.aPoints[i];
	}
	vecForm = _AForm.vecForm;
	vecRoad = _AForm.vecRoad;
};

//==============================
//           Drawer
//==============================
void AForm::drawFormMultiple(string *aString, bool _bDrawlast)
{
	for(int i=0; i<vecForm.size(); i++)
		vecForm[i].drawFormMultiple(aString);
	if(_bDrawlast)
	{
		if(vecForm.size() == 0)
		{
			drawForm(aString);
			Point2D l_center = getCenter();
			Point2D l_p2D(int(l_center.x + BLOCK_SIZE/2 + 0.5), int(l_center.y + BLOCK_SIZE/2 + 0.5));
			if(l_p2D < BLOCK_SIZE && l_p2D > 0 && sName != "-")
				aString[int(l_p2D.y)][int(l_p2D.x)] = sName[0];
		}
	}
	else
	{
		drawForm(aString);
	}
};
	
#ifndef __AForm__
#define __AForm__


#include "maths_Point.h"
#include "maths_Vector.h"
#include "tools.h"
#include <stdio.h>
#include <vector>
#include "EasyBMP.h"
#include "Road.h"

struct AForm;
#include "MainResidence.h"
#include "Residence.h"
struct AForm : Form
{
	vector<AForm> vecForm;
	vector<Road> vecRoad;
	std::string sName;
	bool bSub;

//==============================
//        Constructeur
//==============================
	AForm()
	{
		sName = "-";
		vecForm.clear();
		bSub = true;
	};
	void reset();

//==============================
//         Destructeur
//==============================
	~AForm()
	{};

//==============================
//           Shorten
//==============================
	AForm getShorten(float _fLength);
	bool shorten(float _fLength);
	bool shortenPossible(float _fLength);

//==============================
//         Subdivision
//==============================	
	bool subdivise(bool _bX, float _fmin, float _fdist);//dist between two form
	void subdiviseCreateVec(bool _bX, Vector2D& _vec1, Vector2D& _vec2);
	void create2AForms(bool _bX, AForm& l_AForm1, AForm& l_AForm2);

//==============================
//       Multi_Subdivise
//==============================
	void multiSubdivise(int _n, float _fThickness);
	void multiSubdiviseBuilding(int _n, float _fThickness, float _fDeltaThickness, Residence& _residence, MainResidence& _mainResidence);
	
//==============================
//     Correct_Subdivision
//==============================
	void correctAForm(AForm& _AForm1, AForm& _AForm2);
	void correctVec(bool _bX, int _i, int& _n1, int& _n2, int& _factor, AForm& _AForm);
	void correctPoint(bool _bX, AForm& _AForm1, AForm& _AForm2, Point2D& _p2D, int _i);
	int correctNecessary(Vector2D* _pVec);
	
//==============================
//          Operator
//==============================
	//create Form between two Forms
	AForm operator%(AForm& _AForm);
	void operator=(const AForm& _AForm);

//==============================
//             RNG
//==============================
	float aRng(float _fRng, Vector2D& _vec1, Vector2D& _vec2);
	
//==============================
//           Drawer
//==============================
	void drawFormMultiple(string *aString, bool _bDrawlast = true);

//==============================
//           Travaux
//==============================
	Point2D getLengthMax()
	{
		Vector2D aVec[4];
		Point2D l_p2dMax;
		for(int i=0; i<4; i++)
		{
			aVec[i].define(aPoints[i],aPoints[(i+1)%4]);
		}
		l_p2dMax.define(max(aVec[0].magnitude(), aVec[2].magnitude()),
			max(aVec[1].magnitude(), aVec[3].magnitude()));
		return l_p2dMax;
	};
	Point2D getLengthMin()
	{
		Vector2D aVec[4];
		Point2D l_p2dMax;
		for(int i=0; i<4; i++)
		{
			aVec[i].define(aPoints[i],aPoints[(i+1)%4]);
		}
		l_p2dMax.define(min(aVec[0].magnitude(), aVec[2].magnitude()),
			min(aVec[1].magnitude(), aVec[3].magnitude()));
		return l_p2dMax;
	};
};
#endif

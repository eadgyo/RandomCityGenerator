#ifndef __MAINRESIDENCE__
#define __MAINRESIDENCE__
#include "ResidenceSettings.h"
struct MainResidence;
#include "AdvancedForm.h"
struct MainResidence
{
	MainResidence();

//==============================
//           Use_Map
//==============================
	void addSpBuilding(int _buildType, AForm& _AForm);
	bool nearSpBuilding(int _buildType, AForm& _AForm);

	vector<vector<AForm>> vecvecSpBuilding;
};


#endif
#include "MainResidence.h"

MainResidence::MainResidence()
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	for(int i=0; i<l_resSet.getVecSize(); i++)
	{
		vector<AForm> vecSpBuilding;
		vecvecSpBuilding.push_back(vecSpBuilding);
	}
}

//==============================
//           Use_Map
//==============================
void MainResidence::addSpBuilding(int _buildType, AForm& _AForm)
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	vecvecSpBuilding[_buildType].push_back(_AForm);
}

bool MainResidence::nearSpBuilding(int _buildType, AForm& _AForm)
{
	//variables
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	int l_dist = l_resSet.vecBuildSet[_buildType].fdistMin;
	Vector2D l_vec1;

	for(int i=0; i<vecvecSpBuilding[_buildType].size(); i++)
	{
		if(vecvecSpBuilding[_buildType][i].distMin(_AForm) < l_dist)
			return true;
	}
	return false;
};


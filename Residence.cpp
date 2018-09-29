#include "Residence.h"
Residence::Residence()
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	for(int i=0; i<l_resSet.getVecSize(); i++)
	{
		Building l_building;
		l_building.sName = l_resSet.vecBuildSet[i].sName;
		l_building.remaining = 0;
		vecBuilding.push_back(l_building);
	}
}

bool Residence::createBuilding(AForm& _AForm, MainResidence& _mainResidence)//a ajouter AForm devient un building
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	for(int i=0; i<l_resSet.getVecSize(); i++)
	{
		if(vecBuilding[i].remaining>0 && l_resSet.vecBuildSet[i].mmTaille.compareXOnly(_AForm.getLengthMin())
			&& !_mainResidence.nearSpBuilding(i, _AForm) && Tools::rng(0,5)>3)
		{
			_AForm.sName = l_resSet.vecBuildSet[i].sName[0];
			--vecBuilding[i].remaining;
			_mainResidence.addSpBuilding(i, _AForm);
			return true;
		}
	}
	return false;
}

void Residence::createRng(Residence& _residence, int iLevel, int _iResRemaining)
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	for(int i=0; i<l_resSet.getVecSize(); i++)
	{
		int l_iRemaining = _residence.vecBuilding[i].remaining;
		MinMax l_MinMax = l_resSet.vecBuildSet[i].vecMinMax[iLevel];
		if(l_iRemaining>0)
		{
			int l_iMax = int(l_iRemaining - l_MinMax.xMin*(_residence.iResRemaining - 1));
			if(l_iMax > l_MinMax.xMax)
				vecBuilding[i].remaining = l_MinMax.xMax;
			else if(l_iMax >= l_MinMax.xMin)
				vecBuilding[i].remaining = Tools::rng(int(l_MinMax.xMin), l_iMax);
			else 
				vecBuilding[i].remaining = l_MinMax.xMin;
			_residence.vecBuilding[i].remaining = _residence.vecBuilding[i].remaining - vecBuilding[i].remaining;
		}
	}
	_residence.iResRemaining--;
	iResRemaining = _iResRemaining;
}
	
void Residence::createRng(int iLevel, int _iResRemaining)
{
	ResidenceSet l_resSet = ResidenceSet::getInstance();
	for(int i=0; i<l_resSet.getVecSize(); i++)
	{
		MinMax l_MinMax = l_resSet.vecBuildSet[i].vecMinMax[iLevel];
		vecBuilding[i].remaining = Tools::rng(int(l_MinMax.xMin), int(l_MinMax.xMax));
		iResRemaining = _iResRemaining;
	}
}
